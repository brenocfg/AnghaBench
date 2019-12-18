#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16 ;
struct TYPE_14__ {TYPE_1__* result; int /*<<< orphan*/  copy_is_binary; } ;
struct TYPE_13__ {int format; } ;
struct TYPE_12__ {int numAttributes; TYPE_2__* attDescs; int /*<<< orphan*/  binary; } ;
typedef  TYPE_1__ PGresult ;
typedef  TYPE_2__ PGresAttDesc ;
typedef  TYPE_3__ PGconn ;
typedef  int /*<<< orphan*/  ExecStatusType ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PQclear (TYPE_1__*) ; 
 TYPE_1__* PQmakeEmptyPGresult (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pqGetInt (int*,int,TYPE_3__*) ; 
 scalar_t__ pqGetc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ pqResultAlloc (TYPE_1__*,int,int) ; 

__attribute__((used)) static int
getCopyStart(PGconn *conn, ExecStatusType copytype)
{
	PGresult   *result;
	int			nfields;
	int			i;

	result = PQmakeEmptyPGresult(conn, copytype);
	if (!result)
		goto failure;

	if (pqGetc(&conn->copy_is_binary, conn))
		goto failure;
	result->binary = conn->copy_is_binary;
	/* the next two bytes are the number of fields	*/
	if (pqGetInt(&(result->numAttributes), 2, conn))
		goto failure;
	nfields = result->numAttributes;

	/* allocate space for the attribute descriptors */
	if (nfields > 0)
	{
		result->attDescs = (PGresAttDesc *)
			pqResultAlloc(result, nfields * sizeof(PGresAttDesc), true);
		if (!result->attDescs)
			goto failure;
		MemSet(result->attDescs, 0, nfields * sizeof(PGresAttDesc));
	}

	for (i = 0; i < nfields; i++)
	{
		int			format;

		if (pqGetInt(&format, 2, conn))
			goto failure;

		/*
		 * Since pqGetInt treats 2-byte integers as unsigned, we need to
		 * coerce these results to signed form.
		 */
		format = (int) ((int16) format);
		result->attDescs[i].format = format;
	}

	/* Success! */
	conn->result = result;
	return 0;

failure:
	PQclear(result);
	return EOF;
}