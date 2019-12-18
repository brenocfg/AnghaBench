#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ commandType; int resultRelation; } ;
struct TYPE_8__ {scalar_t__ event; scalar_t__ enabled; } ;
struct TYPE_7__ {int numLocks; TYPE_2__** rules; } ;
typedef  TYPE_1__ RuleLock ;
typedef  TYPE_2__ RewriteRule ;
typedef  TYPE_3__ Query ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ CmdType ;

/* Variables and functions */
 scalar_t__ CMD_SELECT ; 
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ RULE_DISABLED ; 
 scalar_t__ RULE_FIRES_ON_ORIGIN ; 
 scalar_t__ RULE_FIRES_ON_REPLICA ; 
 scalar_t__ SESSION_REPLICATION_ROLE_REPLICA ; 
 scalar_t__ SessionReplicationRole ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ rangeTableEntry_used (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
matchLocks(CmdType event,
		   RuleLock *rulelocks,
		   int varno,
		   Query *parsetree,
		   bool *hasUpdate)
{
	List	   *matching_locks = NIL;
	int			nlocks;
	int			i;

	if (rulelocks == NULL)
		return NIL;

	if (parsetree->commandType != CMD_SELECT)
	{
		if (parsetree->resultRelation != varno)
			return NIL;
	}

	nlocks = rulelocks->numLocks;

	for (i = 0; i < nlocks; i++)
	{
		RewriteRule *oneLock = rulelocks->rules[i];

		if (oneLock->event == CMD_UPDATE)
			*hasUpdate = true;

		/*
		 * Suppress ON INSERT/UPDATE/DELETE rules that are disabled or
		 * configured to not fire during the current sessions replication
		 * role. ON SELECT rules will always be applied in order to keep views
		 * working even in LOCAL or REPLICA role.
		 */
		if (oneLock->event != CMD_SELECT)
		{
			if (SessionReplicationRole == SESSION_REPLICATION_ROLE_REPLICA)
			{
				if (oneLock->enabled == RULE_FIRES_ON_ORIGIN ||
					oneLock->enabled == RULE_DISABLED)
					continue;
			}
			else				/* ORIGIN or LOCAL ROLE */
			{
				if (oneLock->enabled == RULE_FIRES_ON_REPLICA ||
					oneLock->enabled == RULE_DISABLED)
					continue;
			}
		}

		if (oneLock->event == event)
		{
			if (parsetree->commandType != CMD_SELECT ||
				rangeTableEntry_used((Node *) parsetree, varno, 0))
				matching_locks = lappend(matching_locks, oneLock);
		}
	}

	return matching_locks;
}