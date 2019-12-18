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
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int fn_nargs; } ;
struct fp_info {int /*<<< orphan*/ * argtypes; TYPE_1__ flinfo; } ;
typedef  int int16 ;
struct TYPE_17__ {int nargs; TYPE_2__* args; } ;
struct TYPE_16__ {char* data; scalar_t__ cursor; scalar_t__ len; } ;
struct TYPE_15__ {int isnull; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ StringInfoData ;
typedef  TYPE_3__* StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_5__* FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_BINARY_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int FUNC_MAX_ARGS ; 
 int /*<<< orphan*/  OidInputFunctionCall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidReceiveFunctionCall (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,...) ; 
 int /*<<< orphan*/  getTypeBinaryInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getTypeInputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_3__*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pg_client_to_server (char*,int) ; 
 int /*<<< orphan*/  pq_getmsgbytes (TYPE_3__*,int) ; 
 int pq_getmsgint (TYPE_3__*,int) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_3__*) ; 

__attribute__((used)) static int16
parse_fcall_arguments(StringInfo msgBuf, struct fp_info *fip,
					  FunctionCallInfo fcinfo)
{
	int			nargs;
	int			i;
	int			numAFormats;
	int16	   *aformats = NULL;
	StringInfoData abuf;

	/* Get the argument format codes */
	numAFormats = pq_getmsgint(msgBuf, 2);
	if (numAFormats > 0)
	{
		aformats = (int16 *) palloc(numAFormats * sizeof(int16));
		for (i = 0; i < numAFormats; i++)
			aformats[i] = pq_getmsgint(msgBuf, 2);
	}

	nargs = pq_getmsgint(msgBuf, 2);	/* # of arguments */

	if (fip->flinfo.fn_nargs != nargs || nargs > FUNC_MAX_ARGS)
		ereport(ERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("function call message contains %d arguments but function requires %d",
						nargs, fip->flinfo.fn_nargs)));

	fcinfo->nargs = nargs;

	if (numAFormats > 1 && numAFormats != nargs)
		ereport(ERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("function call message contains %d argument formats but %d arguments",
						numAFormats, nargs)));

	initStringInfo(&abuf);

	/*
	 * Copy supplied arguments into arg vector.
	 */
	for (i = 0; i < nargs; ++i)
	{
		int			argsize;
		int16		aformat;

		argsize = pq_getmsgint(msgBuf, 4);
		if (argsize == -1)
		{
			fcinfo->args[i].isnull = true;
		}
		else
		{
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
		}

		if (numAFormats > 1)
			aformat = aformats[i];
		else if (numAFormats > 0)
			aformat = aformats[0];
		else
			aformat = 0;		/* default = text */

		if (aformat == 0)
		{
			Oid			typinput;
			Oid			typioparam;
			char	   *pstring;

			getTypeInputInfo(fip->argtypes[i], &typinput, &typioparam);

			/*
			 * Since stringinfo.c keeps a trailing null in place even for
			 * binary data, the contents of abuf are a valid C string.  We
			 * have to do encoding conversion before calling the typinput
			 * routine, though.
			 */
			if (argsize == -1)
				pstring = NULL;
			else
				pstring = pg_client_to_server(abuf.data, argsize);

			fcinfo->args[i].value = OidInputFunctionCall(typinput, pstring,
														 typioparam, -1);
			/* Free result of encoding conversion, if any */
			if (pstring && pstring != abuf.data)
				pfree(pstring);
		}
		else if (aformat == 1)
		{
			Oid			typreceive;
			Oid			typioparam;
			StringInfo	bufptr;

			/* Call the argument type's binary input converter */
			getTypeBinaryInputInfo(fip->argtypes[i], &typreceive, &typioparam);

			if (argsize == -1)
				bufptr = NULL;
			else
				bufptr = &abuf;

			fcinfo->args[i].value = OidReceiveFunctionCall(typreceive, bufptr,
														   typioparam, -1);

			/* Trouble if it didn't eat the whole buffer */
			if (argsize != -1 && abuf.cursor != abuf.len)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
						 errmsg("incorrect binary data format in function argument %d",
								i + 1)));
		}
		else
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("unsupported format code: %d", aformat)));
	}

	/* Return result format code */
	return (int16) pq_getmsgint(msgBuf, 2);
}