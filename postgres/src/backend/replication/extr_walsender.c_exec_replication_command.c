#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ VariableShowStmt ;
typedef  int /*<<< orphan*/  TimeLineHistoryCmd ;
struct TYPE_12__ {scalar_t__ state; } ;
struct TYPE_11__ {int type; } ;
struct TYPE_10__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ StartReplicationCmd ;
typedef  TYPE_3__ Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  DropReplicationSlotCmd ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  CreateReplicationSlotCmd ;
typedef  int /*<<< orphan*/  BaseBackupCmd ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/ * CreateDestReceiver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateReplicationSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DestRemote ; 
 int /*<<< orphan*/  DestRemoteSimple ; 
 int /*<<< orphan*/  DropReplicationSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_IN_FAILED_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EndCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPGVariable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IdentifySystem () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsA (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsAbortedTransactionBlockState () ; 
 int /*<<< orphan*/  IsTransactionBlock () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 TYPE_7__* MyWalSnd ; 
 int /*<<< orphan*/  PreventInTransactionBlock (int,char*) ; 
 int /*<<< orphan*/  REPLICATION_KIND_PHYSICAL ; 
 int /*<<< orphan*/  SQLCmd ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  STATE_RUNNING ; 
 int /*<<< orphan*/  SendBaseBackup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendTimeLineHistory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SnapBuildClearExportedSnapshot () ; 
 int /*<<< orphan*/  StartLogicalReplication (TYPE_2__*) ; 
 int /*<<< orphan*/  StartReplication (TYPE_2__*) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
#define  T_BaseBackupCmd 135 
#define  T_CreateReplicationSlotCmd 134 
#define  T_DropReplicationSlotCmd 133 
#define  T_IdentifySystemCmd 132 
#define  T_SQLCmd 131 
#define  T_StartReplicationCmd 130 
#define  T_TimeLineHistoryCmd 129 
#define  T_VariableShowStmt 128 
 scalar_t__ WALSNDSTATE_STOPPING ; 
 int /*<<< orphan*/  WalSndSetState (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int) ; 
 scalar_t__ got_STOPPING ; 
 int /*<<< orphan*/  initStringInfo (int /*<<< orphan*/ *) ; 
 scalar_t__ log_replication_commands ; 
 int /*<<< orphan*/  output_message ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* replication_parse_result ; 
 int /*<<< orphan*/  replication_scanner_init (char const*) ; 
 int replication_yyparse () ; 
 int /*<<< orphan*/  reply_message ; 
 int /*<<< orphan*/  tmpbuf ; 

bool
exec_replication_command(const char *cmd_string)
{
	int			parse_rc;
	Node	   *cmd_node;
	MemoryContext cmd_context;
	MemoryContext old_context;

	/*
	 * If WAL sender has been told that shutdown is getting close, switch its
	 * status accordingly to handle the next replication commands correctly.
	 */
	if (got_STOPPING)
		WalSndSetState(WALSNDSTATE_STOPPING);

	/*
	 * Throw error if in stopping mode.  We need prevent commands that could
	 * generate WAL while the shutdown checkpoint is being written.  To be
	 * safe, we just prohibit all new commands.
	 */
	if (MyWalSnd->state == WALSNDSTATE_STOPPING)
		ereport(ERROR,
				(errmsg("cannot execute new commands while WAL sender is in stopping mode")));

	/*
	 * CREATE_REPLICATION_SLOT ... LOGICAL exports a snapshot until the next
	 * command arrives. Clean up the old stuff if there's anything.
	 */
	SnapBuildClearExportedSnapshot();

	CHECK_FOR_INTERRUPTS();

	cmd_context = AllocSetContextCreate(CurrentMemoryContext,
										"Replication command context",
										ALLOCSET_DEFAULT_SIZES);
	old_context = MemoryContextSwitchTo(cmd_context);

	replication_scanner_init(cmd_string);
	parse_rc = replication_yyparse();
	if (parse_rc != 0)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 (errmsg_internal("replication command parser returned %d",
								  parse_rc))));

	cmd_node = replication_parse_result;

	/*
	 * Log replication command if log_replication_commands is enabled. Even
	 * when it's disabled, log the command with DEBUG1 level for backward
	 * compatibility. Note that SQL commands are not logged here, and will be
	 * logged later if log_statement is enabled.
	 */
	if (cmd_node->type != T_SQLCmd)
		ereport(log_replication_commands ? LOG : DEBUG1,
				(errmsg("received replication command: %s", cmd_string)));

	/*
	 * CREATE_REPLICATION_SLOT ... LOGICAL exports a snapshot. If it was
	 * called outside of transaction the snapshot should be cleared here.
	 */
	if (!IsTransactionBlock())
		SnapBuildClearExportedSnapshot();

	/*
	 * For aborted transactions, don't allow anything except pure SQL, the
	 * exec_simple_query() will handle it correctly.
	 */
	if (IsAbortedTransactionBlockState() && !IsA(cmd_node, SQLCmd))
		ereport(ERROR,
				(errcode(ERRCODE_IN_FAILED_SQL_TRANSACTION),
				 errmsg("current transaction is aborted, "
						"commands ignored until end of transaction block")));

	CHECK_FOR_INTERRUPTS();

	/*
	 * Allocate buffers that will be used for each outgoing and incoming
	 * message.  We do this just once per command to reduce palloc overhead.
	 */
	initStringInfo(&output_message);
	initStringInfo(&reply_message);
	initStringInfo(&tmpbuf);

	/* Report to pgstat that this process is running */
	pgstat_report_activity(STATE_RUNNING, NULL);

	switch (cmd_node->type)
	{
		case T_IdentifySystemCmd:
			IdentifySystem();
			break;

		case T_BaseBackupCmd:
			PreventInTransactionBlock(true, "BASE_BACKUP");
			SendBaseBackup((BaseBackupCmd *) cmd_node);
			break;

		case T_CreateReplicationSlotCmd:
			CreateReplicationSlot((CreateReplicationSlotCmd *) cmd_node);
			break;

		case T_DropReplicationSlotCmd:
			DropReplicationSlot((DropReplicationSlotCmd *) cmd_node);
			break;

		case T_StartReplicationCmd:
			{
				StartReplicationCmd *cmd = (StartReplicationCmd *) cmd_node;

				PreventInTransactionBlock(true, "START_REPLICATION");

				if (cmd->kind == REPLICATION_KIND_PHYSICAL)
					StartReplication(cmd);
				else
					StartLogicalReplication(cmd);
				break;
			}

		case T_TimeLineHistoryCmd:
			PreventInTransactionBlock(true, "TIMELINE_HISTORY");
			SendTimeLineHistory((TimeLineHistoryCmd *) cmd_node);
			break;

		case T_VariableShowStmt:
			{
				DestReceiver *dest = CreateDestReceiver(DestRemoteSimple);
				VariableShowStmt *n = (VariableShowStmt *) cmd_node;

				/* syscache access needs a transaction environment */
				StartTransactionCommand();
				GetPGVariable(n->name, dest);
				CommitTransactionCommand();
			}
			break;

		case T_SQLCmd:
			if (MyDatabaseId == InvalidOid)
				ereport(ERROR,
						(errmsg("cannot execute SQL commands in WAL sender for physical replication")));

			/* Report to pgstat that this process is now idle */
			pgstat_report_activity(STATE_IDLE, NULL);

			/* Tell the caller that this wasn't a WalSender command. */
			return false;

		default:
			elog(ERROR, "unrecognized replication command node tag: %u",
				 cmd_node->type);
	}

	/* done */
	MemoryContextSwitchTo(old_context);
	MemoryContextDelete(cmd_context);

	/* Send CommandComplete message */
	EndCommand("SELECT", DestRemote);

	/* Report to pgstat that this process is now idle */
	pgstat_report_activity(STATE_IDLE, NULL);

	return true;
}