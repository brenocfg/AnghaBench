#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ fn_strict; } ;
struct fp_info {int /*<<< orphan*/  fname; int /*<<< orphan*/  rettype; TYPE_7__ flinfo; int /*<<< orphan*/  namespace; } ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_10__ {int nargs; int isnull; TYPE_1__* args; } ;
struct TYPE_9__ {scalar_t__ isnull; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  scalar_t__ Oid ;
typedef  scalar_t__ Datum ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_IN_FAILED_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FUNC_MAX_ARGS ; 
 int /*<<< orphan*/  FrontendProtocol ; 
 scalar_t__ FunctionCallInvoke (TYPE_2__*) ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_2__,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvokeFunctionExecuteHook (scalar_t__) ; 
 int /*<<< orphan*/  InvokeNamespaceSearchHook (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IsAbortedTransactionBlockState () ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ LOGSTMT_ALL ; 
 int /*<<< orphan*/  OBJECT_FUNCTION ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendFunctionResult (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_log_duration (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_2__* fcinfo ; 
 int /*<<< orphan*/  fetch_fp_info (scalar_t__,struct fp_info*) ; 
 int /*<<< orphan*/  get_func_name (scalar_t__) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 scalar_t__ log_statement ; 
 int /*<<< orphan*/  parse_fcall_arguments (int /*<<< orphan*/ ,struct fp_info*,TYPE_2__*) ; 
 int /*<<< orphan*/  parse_fcall_arguments_20 (int /*<<< orphan*/ ,struct fp_info*,TYPE_2__*) ; 
 scalar_t__ pg_namespace_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_proc_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgend (int /*<<< orphan*/ ) ; 
 scalar_t__ pq_getmsgint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_getmsgstring (int /*<<< orphan*/ ) ; 

void
HandleFunctionRequest(StringInfo msgBuf)
{
	LOCAL_FCINFO(fcinfo, FUNC_MAX_ARGS);
	Oid			fid;
	AclResult	aclresult;
	int16		rformat;
	Datum		retval;
	struct fp_info my_fp;
	struct fp_info *fip;
	bool		callit;
	bool		was_logged = false;
	char		msec_str[32];

	/*
	 * We only accept COMMIT/ABORT if we are in an aborted transaction, and
	 * COMMIT/ABORT cannot be executed through the fastpath interface.
	 */
	if (IsAbortedTransactionBlockState())
		ereport(ERROR,
				(errcode(ERRCODE_IN_FAILED_SQL_TRANSACTION),
				 errmsg("current transaction is aborted, "
						"commands ignored until end of transaction block")));

	/*
	 * Now that we know we are in a valid transaction, set snapshot in case
	 * needed by function itself or one of the datatype I/O routines.
	 */
	PushActiveSnapshot(GetTransactionSnapshot());

	/*
	 * Begin parsing the buffer contents.
	 */
	if (PG_PROTOCOL_MAJOR(FrontendProtocol) < 3)
		(void) pq_getmsgstring(msgBuf); /* dummy string */

	fid = (Oid) pq_getmsgint(msgBuf, 4);	/* function oid */

	/*
	 * There used to be a lame attempt at caching lookup info here. Now we
	 * just do the lookups on every call.
	 */
	fip = &my_fp;
	fetch_fp_info(fid, fip);

	/* Log as soon as we have the function OID and name */
	if (log_statement == LOGSTMT_ALL)
	{
		ereport(LOG,
				(errmsg("fastpath function call: \"%s\" (OID %u)",
						fip->fname, fid)));
		was_logged = true;
	}

	/*
	 * Check permission to access and call function.  Since we didn't go
	 * through a normal name lookup, we need to check schema usage too.
	 */
	aclresult = pg_namespace_aclcheck(fip->namespace, GetUserId(), ACL_USAGE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_SCHEMA,
					   get_namespace_name(fip->namespace));
	InvokeNamespaceSearchHook(fip->namespace, true);

	aclresult = pg_proc_aclcheck(fid, GetUserId(), ACL_EXECUTE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_FUNCTION,
					   get_func_name(fid));
	InvokeFunctionExecuteHook(fid);

	/*
	 * Prepare function call info block and insert arguments.
	 *
	 * Note: for now we pass collation = InvalidOid, so collation-sensitive
	 * functions can't be called this way.  Perhaps we should pass
	 * DEFAULT_COLLATION_OID, instead?
	 */
	InitFunctionCallInfoData(*fcinfo, &fip->flinfo, 0, InvalidOid, NULL, NULL);

	if (PG_PROTOCOL_MAJOR(FrontendProtocol) >= 3)
		rformat = parse_fcall_arguments(msgBuf, fip, fcinfo);
	else
		rformat = parse_fcall_arguments_20(msgBuf, fip, fcinfo);

	/* Verify we reached the end of the message where expected. */
	pq_getmsgend(msgBuf);

	/*
	 * If func is strict, must not call it for null args.
	 */
	callit = true;
	if (fip->flinfo.fn_strict)
	{
		int			i;

		for (i = 0; i < fcinfo->nargs; i++)
		{
			if (fcinfo->args[i].isnull)
			{
				callit = false;
				break;
			}
		}
	}

	if (callit)
	{
		/* Okay, do it ... */
		retval = FunctionCallInvoke(fcinfo);
	}
	else
	{
		fcinfo->isnull = true;
		retval = (Datum) 0;
	}

	/* ensure we do at least one CHECK_FOR_INTERRUPTS per function call */
	CHECK_FOR_INTERRUPTS();

	SendFunctionResult(retval, fcinfo->isnull, fip->rettype, rformat);

	/* We no longer need the snapshot */
	PopActiveSnapshot();

	/*
	 * Emit duration logging if appropriate.
	 */
	switch (check_log_duration(msec_str, was_logged))
	{
		case 1:
			ereport(LOG,
					(errmsg("duration: %s ms", msec_str)));
			break;
		case 2:
			ereport(LOG,
					(errmsg("duration: %s ms  fastpath function call: \"%s\" (OID %u)",
							msec_str, fip->fname, fid)));
			break;
	}
}