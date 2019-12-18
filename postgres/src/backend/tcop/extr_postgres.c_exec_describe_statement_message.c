#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_params; scalar_t__ resultDesc; scalar_t__* param_types; int /*<<< orphan*/  fixed_result; } ;
struct TYPE_6__ {TYPE_2__* plansource; } ;
typedef  TYPE_1__ PreparedStatement ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CachedPlanGetTargetList (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ DestRemote ; 
 int /*<<< orphan*/  ERRCODE_IN_FAILED_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_PSTATEMENT ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* FetchPreparedStatement (char const*,int) ; 
 scalar_t__ IsAbortedTransactionBlockState () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MessageContext ; 
 int /*<<< orphan*/  SendRowDescriptionMessage (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_abort () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pq_beginmessage_reuse (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage_reuse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_putemptymessage (char) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  row_description_buf ; 
 int /*<<< orphan*/  start_xact_command () ; 
 TYPE_2__* unnamed_stmt_psrc ; 
 scalar_t__ whereToSendOutput ; 

__attribute__((used)) static void
exec_describe_statement_message(const char *stmt_name)
{
	CachedPlanSource *psrc;

	/*
	 * Start up a transaction command. (Note that this will normally change
	 * current memory context.) Nothing happens if we are already in one.
	 */
	start_xact_command();

	/* Switch back to message context */
	MemoryContextSwitchTo(MessageContext);

	/* Find prepared statement */
	if (stmt_name[0] != '\0')
	{
		PreparedStatement *pstmt;

		pstmt = FetchPreparedStatement(stmt_name, true);
		psrc = pstmt->plansource;
	}
	else
	{
		/* special-case the unnamed statement */
		psrc = unnamed_stmt_psrc;
		if (!psrc)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_PSTATEMENT),
					 errmsg("unnamed prepared statement does not exist")));
	}

	/* Prepared statements shouldn't have changeable result descs */
	Assert(psrc->fixed_result);

	/*
	 * If we are in aborted transaction state, we can't run
	 * SendRowDescriptionMessage(), because that needs catalog accesses.
	 * Hence, refuse to Describe statements that return data.  (We shouldn't
	 * just refuse all Describes, since that might break the ability of some
	 * clients to issue COMMIT or ROLLBACK commands, if they use code that
	 * blindly Describes whatever it does.)  We can Describe parameters
	 * without doing anything dangerous, so we don't restrict that.
	 */
	if (IsAbortedTransactionBlockState() &&
		psrc->resultDesc)
		ereport(ERROR,
				(errcode(ERRCODE_IN_FAILED_SQL_TRANSACTION),
				 errmsg("current transaction is aborted, "
						"commands ignored until end of transaction block"),
				 errdetail_abort()));

	if (whereToSendOutput != DestRemote)
		return;					/* can't actually do anything... */

	/*
	 * First describe the parameters...
	 */
	pq_beginmessage_reuse(&row_description_buf, 't');	/* parameter description
														 * message type */
	pq_sendint16(&row_description_buf, psrc->num_params);

	for (int i = 0; i < psrc->num_params; i++)
	{
		Oid			ptype = psrc->param_types[i];

		pq_sendint32(&row_description_buf, (int) ptype);
	}
	pq_endmessage_reuse(&row_description_buf);

	/*
	 * Next send RowDescription or NoData to describe the result...
	 */
	if (psrc->resultDesc)
	{
		List	   *tlist;

		/* Get the plan's primary targetlist */
		tlist = CachedPlanGetTargetList(psrc, NULL);

		SendRowDescriptionMessage(&row_description_buf,
								  psrc->resultDesc,
								  tlist,
								  NULL);
	}
	else
		pq_putemptymessage('n');	/* NoData */

}