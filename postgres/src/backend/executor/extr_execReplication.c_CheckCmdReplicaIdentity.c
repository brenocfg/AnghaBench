#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pubdelete; scalar_t__ pubupdate; } ;
struct TYPE_10__ {TYPE_1__* rd_rel; } ;
struct TYPE_9__ {scalar_t__ relreplident; } ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__ PublicationActions ;
typedef  scalar_t__ CmdType ;

/* Variables and functions */
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_3__* GetRelationPublicationActions (TYPE_2__*) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ REPLICA_IDENTITY_FULL ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetReplicaIndex (TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

void
CheckCmdReplicaIdentity(Relation rel, CmdType cmd)
{
	PublicationActions *pubactions;

	/* We only need to do checks for UPDATE and DELETE. */
	if (cmd != CMD_UPDATE && cmd != CMD_DELETE)
		return;

	/* If relation has replica identity we are always good. */
	if (rel->rd_rel->relreplident == REPLICA_IDENTITY_FULL ||
		OidIsValid(RelationGetReplicaIndex(rel)))
		return;

	/*
	 * This is either UPDATE OR DELETE and there is no replica identity.
	 *
	 * Check if the table publishes UPDATES or DELETES.
	 */
	pubactions = GetRelationPublicationActions(rel);
	if (cmd == CMD_UPDATE && pubactions->pubupdate)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("cannot update table \"%s\" because it does not have a replica identity and publishes updates",
						RelationGetRelationName(rel)),
				 errhint("To enable updating the table, set REPLICA IDENTITY using ALTER TABLE.")));
	else if (cmd == CMD_DELETE && pubactions->pubdelete)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("cannot delete from table \"%s\" because it does not have a replica identity and publishes deletes",
						RelationGetRelationName(rel)),
				 errhint("To enable deleting from the table, set REPLICA IDENTITY using ALTER TABLE.")));
}