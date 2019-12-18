#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int subtype; int /*<<< orphan*/  name; int /*<<< orphan*/  def; int /*<<< orphan*/  num; } ;
struct TYPE_15__ {int /*<<< orphan*/ * subcmds; int /*<<< orphan*/  newrelpersistence; int /*<<< orphan*/  rewrite; void* chgPersistence; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__ AlteredTableInfo ;
typedef  TYPE_2__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  ATCheckPartitionsNotInUse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ATGetQueueEntry (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATPrepAddColumn (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATPrepAddInherit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATPrepAlterColumnType (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* ATPrepChangePersistence (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATPrepDropColumn (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATPrepDropNotNull (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ATPrepSetNotNull (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATPrepSetStatistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATPrepSetTableSpace (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATSimplePermissions (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATSimpleRecursion (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int ATT_COMPOSITE_TYPE ; 
 int ATT_FOREIGN_TABLE ; 
 int ATT_INDEX ; 
 int ATT_MATVIEW ; 
 int ATT_PARTITIONED_INDEX ; 
 int ATT_TABLE ; 
 int ATT_VIEW ; 
#define  AT_AddColumn 183 
#define  AT_AddColumnToView 182 
#define  AT_AddConstraint 181 
 int AT_AddConstraintRecurse ; 
#define  AT_AddIdentity 180 
#define  AT_AddIndex 179 
#define  AT_AddIndexConstraint 178 
#define  AT_AddInherit 177 
#define  AT_AddOf 176 
#define  AT_AlterColumnGenericOptions 175 
#define  AT_AlterColumnType 174 
#define  AT_AlterConstraint 173 
#define  AT_AttachPartition 172 
#define  AT_ChangeOwner 171 
#define  AT_CheckNotNull 170 
#define  AT_ClusterOn 169 
#define  AT_ColumnDefault 168 
#define  AT_DetachPartition 167 
#define  AT_DisableRowSecurity 166 
#define  AT_DisableRule 165 
#define  AT_DisableTrig 164 
#define  AT_DisableTrigAll 163 
#define  AT_DisableTrigUser 162 
#define  AT_DropCluster 161 
#define  AT_DropColumn 160 
#define  AT_DropConstraint 159 
 int AT_DropConstraintRecurse ; 
#define  AT_DropIdentity 158 
#define  AT_DropInherit 157 
#define  AT_DropNotNull 156 
#define  AT_DropOf 155 
#define  AT_DropOids 154 
#define  AT_EnableAlwaysRule 153 
#define  AT_EnableAlwaysTrig 152 
#define  AT_EnableReplicaRule 151 
#define  AT_EnableReplicaTrig 150 
#define  AT_EnableRowSecurity 149 
#define  AT_EnableRule 148 
#define  AT_EnableTrig 147 
#define  AT_EnableTrigAll 146 
#define  AT_EnableTrigUser 145 
#define  AT_ForceRowSecurity 144 
#define  AT_GenericOptions 143 
#define  AT_NoForceRowSecurity 142 
 int AT_PASS_ADD_COL ; 
 int AT_PASS_ADD_CONSTR ; 
 int AT_PASS_ADD_INDEX ; 
 int AT_PASS_ALTER_TYPE ; 
 int AT_PASS_COL_ATTRS ; 
 int AT_PASS_DROP ; 
 int AT_PASS_MISC ; 
 int AT_PASS_UNSET ; 
 int /*<<< orphan*/  AT_REWRITE_ALTER_PERSISTENCE ; 
#define  AT_ReplaceRelOptions 141 
#define  AT_ReplicaIdentity 140 
#define  AT_ResetOptions 139 
#define  AT_ResetRelOptions 138 
#define  AT_SetIdentity 137 
#define  AT_SetLogged 136 
#define  AT_SetNotNull 135 
#define  AT_SetOptions 134 
#define  AT_SetRelOptions 133 
#define  AT_SetStatistics 132 
#define  AT_SetStorage 131 
#define  AT_SetTableSpace 130 
#define  AT_SetUnLogged 129 
#define  AT_ValidateConstraint 128 
 int AT_ValidateConstraintRecurse ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RELPERSISTENCE_PERMANENT ; 
 int /*<<< orphan*/  RELPERSISTENCE_UNLOGGED ; 
 TYPE_2__* copyObject (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
ATPrepCmd(List **wqueue, Relation rel, AlterTableCmd *cmd,
		  bool recurse, bool recursing, LOCKMODE lockmode)
{
	AlteredTableInfo *tab;
	int			pass = AT_PASS_UNSET;

	/* Find or create work queue entry for this table */
	tab = ATGetQueueEntry(wqueue, rel);

	/*
	 * Copy the original subcommand for each table.  This avoids conflicts
	 * when different child tables need to make different parse
	 * transformations (for example, the same column may have different column
	 * numbers in different children).
	 */
	cmd = copyObject(cmd);

	/*
	 * Do permissions checking, recursion to child tables if needed, and any
	 * additional phase-1 processing needed.
	 */
	switch (cmd->subtype)
	{
		case AT_AddColumn:		/* ADD COLUMN */
			ATSimplePermissions(rel,
								ATT_TABLE | ATT_COMPOSITE_TYPE | ATT_FOREIGN_TABLE);
			ATPrepAddColumn(wqueue, rel, recurse, recursing, false, cmd,
							lockmode);
			/* Recursion occurs during execution phase */
			pass = AT_PASS_ADD_COL;
			break;
		case AT_AddColumnToView:	/* add column via CREATE OR REPLACE VIEW */
			ATSimplePermissions(rel, ATT_VIEW);
			ATPrepAddColumn(wqueue, rel, recurse, recursing, true, cmd,
							lockmode);
			/* Recursion occurs during execution phase */
			pass = AT_PASS_ADD_COL;
			break;
		case AT_ColumnDefault:	/* ALTER COLUMN DEFAULT */

			/*
			 * We allow defaults on views so that INSERT into a view can have
			 * default-ish behavior.  This works because the rewriter
			 * substitutes default values into INSERTs before it expands
			 * rules.
			 */
			ATSimplePermissions(rel, ATT_TABLE | ATT_VIEW | ATT_FOREIGN_TABLE);
			ATSimpleRecursion(wqueue, rel, cmd, recurse, lockmode);
			/* No command-specific prep needed */
			pass = cmd->def ? AT_PASS_ADD_CONSTR : AT_PASS_DROP;
			break;
		case AT_AddIdentity:
			ATSimplePermissions(rel, ATT_TABLE | ATT_VIEW | ATT_FOREIGN_TABLE);
			/* This command never recurses */
			pass = AT_PASS_ADD_CONSTR;
			break;
		case AT_SetIdentity:
			ATSimplePermissions(rel, ATT_TABLE | ATT_VIEW | ATT_FOREIGN_TABLE);
			/* This command never recurses */
			pass = AT_PASS_COL_ATTRS;
			break;
		case AT_DropIdentity:
			ATSimplePermissions(rel, ATT_TABLE | ATT_VIEW | ATT_FOREIGN_TABLE);
			/* This command never recurses */
			pass = AT_PASS_DROP;
			break;
		case AT_DropNotNull:	/* ALTER COLUMN DROP NOT NULL */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			ATPrepDropNotNull(rel, recurse, recursing);
			ATSimpleRecursion(wqueue, rel, cmd, recurse, lockmode);
			pass = AT_PASS_DROP;
			break;
		case AT_SetNotNull:		/* ALTER COLUMN SET NOT NULL */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			/* Need command-specific recursion decision */
			ATPrepSetNotNull(wqueue, rel, cmd, recurse, recursing, lockmode);
			pass = AT_PASS_COL_ATTRS;
			break;
		case AT_CheckNotNull:	/* check column is already marked NOT NULL */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			ATSimpleRecursion(wqueue, rel, cmd, recurse, lockmode);
			/* No command-specific prep needed */
			pass = AT_PASS_COL_ATTRS;
			break;
		case AT_SetStatistics:	/* ALTER COLUMN SET STATISTICS */
			ATSimpleRecursion(wqueue, rel, cmd, recurse, lockmode);
			/* Performs own permission checks */
			ATPrepSetStatistics(rel, cmd->name, cmd->num, cmd->def, lockmode);
			pass = AT_PASS_MISC;
			break;
		case AT_SetOptions:		/* ALTER COLUMN SET ( options ) */
		case AT_ResetOptions:	/* ALTER COLUMN RESET ( options ) */
			ATSimplePermissions(rel, ATT_TABLE | ATT_MATVIEW | ATT_INDEX | ATT_FOREIGN_TABLE);
			/* This command never recurses */
			pass = AT_PASS_MISC;
			break;
		case AT_SetStorage:		/* ALTER COLUMN SET STORAGE */
			ATSimplePermissions(rel, ATT_TABLE | ATT_MATVIEW | ATT_FOREIGN_TABLE);
			ATSimpleRecursion(wqueue, rel, cmd, recurse, lockmode);
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_DropColumn:		/* DROP COLUMN */
			ATSimplePermissions(rel,
								ATT_TABLE | ATT_COMPOSITE_TYPE | ATT_FOREIGN_TABLE);
			ATPrepDropColumn(wqueue, rel, recurse, recursing, cmd, lockmode);
			/* Recursion occurs during execution phase */
			pass = AT_PASS_DROP;
			break;
		case AT_AddIndex:		/* ADD INDEX */
			ATSimplePermissions(rel, ATT_TABLE);
			/* This command never recurses */
			/* No command-specific prep needed */
			pass = AT_PASS_ADD_INDEX;
			break;
		case AT_AddConstraint:	/* ADD CONSTRAINT */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			/* Recursion occurs during execution phase */
			/* No command-specific prep needed except saving recurse flag */
			if (recurse)
				cmd->subtype = AT_AddConstraintRecurse;
			pass = AT_PASS_ADD_CONSTR;
			break;
		case AT_AddIndexConstraint: /* ADD CONSTRAINT USING INDEX */
			ATSimplePermissions(rel, ATT_TABLE);
			/* This command never recurses */
			/* No command-specific prep needed */
			pass = AT_PASS_ADD_CONSTR;
			break;
		case AT_DropConstraint: /* DROP CONSTRAINT */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			ATCheckPartitionsNotInUse(rel, lockmode);
			/* Other recursion occurs during execution phase */
			/* No command-specific prep needed except saving recurse flag */
			if (recurse)
				cmd->subtype = AT_DropConstraintRecurse;
			pass = AT_PASS_DROP;
			break;
		case AT_AlterColumnType:	/* ALTER COLUMN TYPE */
			ATSimplePermissions(rel,
								ATT_TABLE | ATT_COMPOSITE_TYPE | ATT_FOREIGN_TABLE);
			/* Performs own recursion */
			ATPrepAlterColumnType(wqueue, tab, rel, recurse, recursing, cmd, lockmode);
			pass = AT_PASS_ALTER_TYPE;
			break;
		case AT_AlterColumnGenericOptions:
			ATSimplePermissions(rel, ATT_FOREIGN_TABLE);
			/* This command never recurses */
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_ChangeOwner:	/* ALTER OWNER */
			/* This command never recurses */
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_ClusterOn:		/* CLUSTER ON */
		case AT_DropCluster:	/* SET WITHOUT CLUSTER */
			ATSimplePermissions(rel, ATT_TABLE | ATT_MATVIEW);
			/* These commands never recurse */
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_SetLogged:		/* SET LOGGED */
			ATSimplePermissions(rel, ATT_TABLE);
			tab->chgPersistence = ATPrepChangePersistence(rel, true);
			/* force rewrite if necessary; see comment in ATRewriteTables */
			if (tab->chgPersistence)
			{
				tab->rewrite |= AT_REWRITE_ALTER_PERSISTENCE;
				tab->newrelpersistence = RELPERSISTENCE_PERMANENT;
			}
			pass = AT_PASS_MISC;
			break;
		case AT_SetUnLogged:	/* SET UNLOGGED */
			ATSimplePermissions(rel, ATT_TABLE);
			tab->chgPersistence = ATPrepChangePersistence(rel, false);
			/* force rewrite if necessary; see comment in ATRewriteTables */
			if (tab->chgPersistence)
			{
				tab->rewrite |= AT_REWRITE_ALTER_PERSISTENCE;
				tab->newrelpersistence = RELPERSISTENCE_UNLOGGED;
			}
			pass = AT_PASS_MISC;
			break;
		case AT_DropOids:		/* SET WITHOUT OIDS */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			pass = AT_PASS_DROP;
			break;
		case AT_SetTableSpace:	/* SET TABLESPACE */
			ATSimplePermissions(rel, ATT_TABLE | ATT_MATVIEW | ATT_INDEX |
								ATT_PARTITIONED_INDEX);
			/* This command never recurses */
			ATPrepSetTableSpace(tab, rel, cmd->name, lockmode);
			pass = AT_PASS_MISC;	/* doesn't actually matter */
			break;
		case AT_SetRelOptions:	/* SET (...) */
		case AT_ResetRelOptions:	/* RESET (...) */
		case AT_ReplaceRelOptions:	/* reset them all, then set just these */
			ATSimplePermissions(rel, ATT_TABLE | ATT_VIEW | ATT_MATVIEW | ATT_INDEX);
			/* This command never recurses */
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_AddInherit:		/* INHERIT */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			/* This command never recurses */
			ATPrepAddInherit(rel);
			pass = AT_PASS_MISC;
			break;
		case AT_DropInherit:	/* NO INHERIT */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			/* This command never recurses */
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_AlterConstraint:	/* ALTER CONSTRAINT */
			ATSimplePermissions(rel, ATT_TABLE);
			pass = AT_PASS_MISC;
			break;
		case AT_ValidateConstraint: /* VALIDATE CONSTRAINT */
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			/* Recursion occurs during execution phase */
			/* No command-specific prep needed except saving recurse flag */
			if (recurse)
				cmd->subtype = AT_ValidateConstraintRecurse;
			pass = AT_PASS_MISC;
			break;
		case AT_ReplicaIdentity:	/* REPLICA IDENTITY ... */
			ATSimplePermissions(rel, ATT_TABLE | ATT_MATVIEW);
			pass = AT_PASS_MISC;
			/* This command never recurses */
			/* No command-specific prep needed */
			break;
		case AT_EnableTrig:		/* ENABLE TRIGGER variants */
		case AT_EnableAlwaysTrig:
		case AT_EnableReplicaTrig:
		case AT_EnableTrigAll:
		case AT_EnableTrigUser:
		case AT_DisableTrig:	/* DISABLE TRIGGER variants */
		case AT_DisableTrigAll:
		case AT_DisableTrigUser:
			ATSimplePermissions(rel, ATT_TABLE | ATT_FOREIGN_TABLE);
			pass = AT_PASS_MISC;
			break;
		case AT_EnableRule:		/* ENABLE/DISABLE RULE variants */
		case AT_EnableAlwaysRule:
		case AT_EnableReplicaRule:
		case AT_DisableRule:
		case AT_AddOf:			/* OF */
		case AT_DropOf:			/* NOT OF */
		case AT_EnableRowSecurity:
		case AT_DisableRowSecurity:
		case AT_ForceRowSecurity:
		case AT_NoForceRowSecurity:
			ATSimplePermissions(rel, ATT_TABLE);
			/* These commands never recurse */
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_GenericOptions:
			ATSimplePermissions(rel, ATT_FOREIGN_TABLE);
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_AttachPartition:
			ATSimplePermissions(rel, ATT_TABLE | ATT_PARTITIONED_INDEX);
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		case AT_DetachPartition:
			ATSimplePermissions(rel, ATT_TABLE);
			/* No command-specific prep needed */
			pass = AT_PASS_MISC;
			break;
		default:				/* oops */
			elog(ERROR, "unrecognized alter table type: %d",
				 (int) cmd->subtype);
			pass = AT_PASS_UNSET;	/* keep compiler quiet */
			break;
	}
	Assert(pass > AT_PASS_UNSET);

	/* Add the subcommand to the appropriate list for phase 2 */
	tab->subcmds[pass] = lappend(tab->subcmds[pass], cmd);
}