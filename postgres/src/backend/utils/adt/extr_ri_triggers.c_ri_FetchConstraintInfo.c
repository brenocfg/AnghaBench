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
struct TYPE_6__ {scalar_t__ tgconstrrelid; int /*<<< orphan*/  tgname; int /*<<< orphan*/  tgconstraint; } ;
typedef  TYPE_1__ Trigger ;
struct TYPE_7__ {scalar_t__ fk_relid; scalar_t__ pk_relid; scalar_t__ confmatchtype; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ RI_ConstraintInfo ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FKCONSTR_MATCH_FULL ; 
 scalar_t__ FKCONSTR_MATCH_PARTIAL ; 
 scalar_t__ FKCONSTR_MATCH_SIMPLE ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_2__* ri_LoadConstraintInfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const RI_ConstraintInfo *
ri_FetchConstraintInfo(Trigger *trigger, Relation trig_rel, bool rel_is_pk)
{
	Oid			constraintOid = trigger->tgconstraint;
	const RI_ConstraintInfo *riinfo;

	/*
	 * Check that the FK constraint's OID is available; it might not be if
	 * we've been invoked via an ordinary trigger or an old-style "constraint
	 * trigger".
	 */
	if (!OidIsValid(constraintOid))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("no pg_constraint entry for trigger \"%s\" on table \"%s\"",
						trigger->tgname, RelationGetRelationName(trig_rel)),
				 errhint("Remove this referential integrity trigger and its mates, then do ALTER TABLE ADD CONSTRAINT.")));

	/* Find or create a hashtable entry for the constraint */
	riinfo = ri_LoadConstraintInfo(constraintOid);

	/* Do some easy cross-checks against the trigger call data */
	if (rel_is_pk)
	{
		if (riinfo->fk_relid != trigger->tgconstrrelid ||
			riinfo->pk_relid != RelationGetRelid(trig_rel))
			elog(ERROR, "wrong pg_constraint entry for trigger \"%s\" on table \"%s\"",
				 trigger->tgname, RelationGetRelationName(trig_rel));
	}
	else
	{
		if (riinfo->fk_relid != RelationGetRelid(trig_rel) ||
			riinfo->pk_relid != trigger->tgconstrrelid)
			elog(ERROR, "wrong pg_constraint entry for trigger \"%s\" on table \"%s\"",
				 trigger->tgname, RelationGetRelationName(trig_rel));
	}

	if (riinfo->confmatchtype != FKCONSTR_MATCH_FULL &&
		riinfo->confmatchtype != FKCONSTR_MATCH_PARTIAL &&
		riinfo->confmatchtype != FKCONSTR_MATCH_SIMPLE)
		elog(ERROR, "unrecognized confmatchtype: %d",
			 riinfo->confmatchtype);

	if (riinfo->confmatchtype == FKCONSTR_MATCH_PARTIAL)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("MATCH PARTIAL not yet implemented")));

	return riinfo;
}