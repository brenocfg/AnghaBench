#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int fn_nargs; } ;
struct fp_info {int /*<<< orphan*/ * argtypes; TYPE_1__ flinfo; } ;
typedef  int int16 ;
struct TYPE_13__ {int nargs; TYPE_2__* args; } ;
struct TYPE_12__ {scalar_t__ cursor; scalar_t__ len; } ;
struct TYPE_11__ {int isnull; void* value; } ;
typedef  TYPE_3__ StringInfoData ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__* FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_BINARY_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int FUNC_MAX_ARGS ; 
 void* OidReceiveFunctionCall (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,...) ; 
 int /*<<< orphan*/  getTypeBinaryInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  pq_getmsgbytes (int /*<<< orphan*/ ,int) ; 
 int pq_getmsgint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_3__*) ; 

__attribute__((used)) static int16
parse_fcall_arguments_20(StringInfo msgBuf, struct fp_info *fip,
						 FunctionCallInfo fcinfo)
{
	int			nargs;
	int			i;
	StringInfoData abuf;

	nargs = pq_getmsgint(msgBuf, 4);	/* # of arguments */

	if (fip->flinfo.fn_nargs != nargs || nargs > FUNC_MAX_ARGS)
		ereport(ERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("function call message contains %d arguments but function requires %d",
						nargs, fip->flinfo.fn_nargs)));

	fcinfo->nargs = nargs;

	initStringInfo(&abuf);

	/*
	 * Copy supplied arguments into arg vector.  In protocol 2.0 these are
	 * always assumed to be supplied in binary format.
	 *
	 * Note: although the original protocol 2.0 code did not have any way for
	 * the frontend to specify a NULL argument, we now choose to interpret
	 * length == -1 as meaning a NULL.
	 */
	for (i = 0; i < nargs; ++i)
	{
		int			argsize;
		Oid			typreceive;
		Oid			typioparam;

		getTypeBinaryInputInfo(fip->argtypes[i], &typreceive, &typioparam);

		argsize = pq_getmsgint(msgBuf, 4);
		if (argsize == -1)
		{
			fcinfo->args[i].isnull = true;
			fcinfo->args[i].value = OidReceiveFunctionCall(typreceive, NULL,
														   typioparam, -1);
			continue;
		}
		fcinfo->args[i].isnull = false;
		if (argsize < 0)
			ereport(ERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("invalid argument size %d in function call message",
							argsize)));

		/* Reset abuf to empty, and insert raw data into it */
		resetStringInfo(&abuf);
		appendBinaryStringInfo(&abuf,
							   pq_getmsgbytes(msgBuf, argsize),
							   argsize);

		fcinfo->args[i].value = OidReceiveFunctionCall(typreceive, &abuf,
													   typioparam, -1);

		/* Trouble if it didn't eat the whole buffer */
		if (abuf.cursor != abuf.len)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
					 errmsg("incorrect binary data format in function argument %d",
							i + 1)));
	}

	/* Desired result format is always binary in protocol 2.0 */
	return 1;
}