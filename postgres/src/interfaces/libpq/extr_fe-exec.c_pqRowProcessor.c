#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_2__* result; int /*<<< orphan*/  asyncStatus; TYPE_2__* next_result; scalar_t__ singleRowMode; TYPE_4__* rowBuf; } ;
struct TYPE_16__ {int len; int /*<<< orphan*/  value; } ;
struct TYPE_15__ {int len; char* value; } ;
struct TYPE_14__ {int numAttributes; char* null_field; int /*<<< orphan*/  resultStatus; TYPE_1__* attDescs; } ;
struct TYPE_13__ {scalar_t__ format; } ;
typedef  TYPE_2__ PGresult ;
typedef  TYPE_3__ PGresAttValue ;
typedef  TYPE_4__ PGdataValue ;
typedef  TYPE_5__ PGconn ;

/* Variables and functions */
 int NULL_LEN ; 
 int /*<<< orphan*/  PGASYNC_READY ; 
 int /*<<< orphan*/  PGRES_SINGLE_TUPLE ; 
 int PG_COPYRES_ATTRS ; 
 int PG_COPYRES_EVENTS ; 
 int PG_COPYRES_NOTICEHOOKS ; 
 int /*<<< orphan*/  PQclear (TYPE_2__*) ; 
 TYPE_2__* PQcopyResult (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pqAddTuple (TYPE_2__*,TYPE_3__*,char const**) ; 
 scalar_t__ pqResultAlloc (TYPE_2__*,int,int) ; 

int
pqRowProcessor(PGconn *conn, const char **errmsgp)
{
	PGresult   *res = conn->result;
	int			nfields = res->numAttributes;
	const PGdataValue *columns = conn->rowBuf;
	PGresAttValue *tup;
	int			i;

	/*
	 * In single-row mode, make a new PGresult that will hold just this one
	 * row; the original conn->result is left unchanged so that it can be used
	 * again as the template for future rows.
	 */
	if (conn->singleRowMode)
	{
		/* Copy everything that should be in the result at this point */
		res = PQcopyResult(res,
						   PG_COPYRES_ATTRS | PG_COPYRES_EVENTS |
						   PG_COPYRES_NOTICEHOOKS);
		if (!res)
			return 0;
	}

	/*
	 * Basically we just allocate space in the PGresult for each field and
	 * copy the data over.
	 *
	 * Note: on malloc failure, we return 0 leaving *errmsgp still NULL, which
	 * caller will take to mean "out of memory".  This is preferable to trying
	 * to set up such a message here, because evidently there's not enough
	 * memory for gettext() to do anything.
	 */
	tup = (PGresAttValue *)
		pqResultAlloc(res, nfields * sizeof(PGresAttValue), true);
	if (tup == NULL)
		goto fail;

	for (i = 0; i < nfields; i++)
	{
		int			clen = columns[i].len;

		if (clen < 0)
		{
			/* null field */
			tup[i].len = NULL_LEN;
			tup[i].value = res->null_field;
		}
		else
		{
			bool		isbinary = (res->attDescs[i].format != 0);
			char	   *val;

			val = (char *) pqResultAlloc(res, clen + 1, isbinary);
			if (val == NULL)
				goto fail;

			/* copy and zero-terminate the data (even if it's binary) */
			memcpy(val, columns[i].value, clen);
			val[clen] = '\0';

			tup[i].len = clen;
			tup[i].value = val;
		}
	}

	/* And add the tuple to the PGresult's tuple array */
	if (!pqAddTuple(res, tup, errmsgp))
		goto fail;

	/*
	 * Success.  In single-row mode, make the result available to the client
	 * immediately.
	 */
	if (conn->singleRowMode)
	{
		/* Change result status to special single-row value */
		res->resultStatus = PGRES_SINGLE_TUPLE;
		/* Stash old result for re-use later */
		conn->next_result = conn->result;
		conn->result = res;
		/* And mark the result ready to return */
		conn->asyncStatus = PGASYNC_READY;
	}

	return 1;

fail:
	/* release locally allocated PGresult, if we made one */
	if (res != conn->result)
		PQclear(res);
	return 0;
}