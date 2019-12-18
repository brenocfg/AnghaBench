#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int resultRelation; scalar_t__ commandType; TYPE_1__* onConflict; } ;
struct TYPE_7__ {scalar_t__ relkind; int requiredPerms; scalar_t__ checkAsUser; int /*<<< orphan*/  relid; } ;
struct TYPE_6__ {scalar_t__ action; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  TYPE_3__ Query ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ CmdType ;

/* Variables and functions */
 int ACL_SELECT ; 
 int ACL_UPDATE ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_INSERT ; 
 scalar_t__ CMD_SELECT ; 
 scalar_t__ CMD_UPDATE ; 
 scalar_t__ GetUserId () ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ ONCONFLICT_UPDATE ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 int RLS_NONE ; 
 int RLS_NONE_ENV ; 
 int /*<<< orphan*/  WCO_RLS_CONFLICT_CHECK ; 
 int /*<<< orphan*/  WCO_RLS_INSERT_CHECK ; 
 int /*<<< orphan*/  WCO_RLS_UPDATE_CHECK ; 
 int /*<<< orphan*/  add_security_quals (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  add_with_check_options (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*,int) ; 
 int check_enable_rls (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  get_policies_for_relation (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  setRuleCheckAsUser (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
get_row_security_policies(Query *root, RangeTblEntry *rte, int rt_index,
						  List **securityQuals, List **withCheckOptions,
						  bool *hasRowSecurity, bool *hasSubLinks)
{
	Oid			user_id;
	int			rls_status;
	Relation	rel;
	CmdType		commandType;
	List	   *permissive_policies;
	List	   *restrictive_policies;

	/* Defaults for the return values */
	*securityQuals = NIL;
	*withCheckOptions = NIL;
	*hasRowSecurity = false;
	*hasSubLinks = false;

	/* If this is not a normal relation, just return immediately */
	if (rte->relkind != RELKIND_RELATION &&
		rte->relkind != RELKIND_PARTITIONED_TABLE)
		return;

	/* Switch to checkAsUser if it's set */
	user_id = rte->checkAsUser ? rte->checkAsUser : GetUserId();

	/* Determine the state of RLS for this, pass checkAsUser explicitly */
	rls_status = check_enable_rls(rte->relid, rte->checkAsUser, false);

	/* If there is no RLS on this table at all, nothing to do */
	if (rls_status == RLS_NONE)
		return;

	/*
	 * RLS_NONE_ENV means we are not doing any RLS now, but that may change
	 * with changes to the environment, so we mark it as hasRowSecurity to
	 * force a re-plan when the environment changes.
	 */
	if (rls_status == RLS_NONE_ENV)
	{
		/*
		 * Indicate that this query may involve RLS and must therefore be
		 * replanned if the environment changes (GUCs, role), but we are not
		 * adding anything here.
		 */
		*hasRowSecurity = true;

		return;
	}

	/*
	 * RLS is enabled for this relation.
	 *
	 * Get the security policies that should be applied, based on the command
	 * type.  Note that if this isn't the target relation, we actually want
	 * the relation's SELECT policies, regardless of the query command type,
	 * for example in UPDATE t1 ... FROM t2 we need to apply t1's UPDATE
	 * policies and t2's SELECT policies.
	 */
	rel = table_open(rte->relid, NoLock);

	commandType = rt_index == root->resultRelation ?
		root->commandType : CMD_SELECT;

	/*
	 * In some cases, we need to apply USING policies (which control the
	 * visibility of records) associated with multiple command types (see
	 * specific cases below).
	 *
	 * When considering the order in which to apply these USING policies, we
	 * prefer to apply higher privileged policies, those which allow the user
	 * to lock records (UPDATE and DELETE), first, followed by policies which
	 * don't (SELECT).
	 *
	 * Note that the optimizer is free to push down and reorder quals which
	 * use leakproof functions.
	 *
	 * In all cases, if there are no policy clauses allowing access to rows in
	 * the table for the specific type of operation, then a single
	 * always-false clause (a default-deny policy) will be added (see
	 * add_security_quals).
	 */

	/*
	 * For a SELECT, if UPDATE privileges are required (eg: the user has
	 * specified FOR [KEY] UPDATE/SHARE), then add the UPDATE USING quals
	 * first.
	 *
	 * This way, we filter out any records from the SELECT FOR SHARE/UPDATE
	 * which the user does not have access to via the UPDATE USING policies,
	 * similar to how we require normal UPDATE rights for these queries.
	 */
	if (commandType == CMD_SELECT && rte->requiredPerms & ACL_UPDATE)
	{
		List	   *update_permissive_policies;
		List	   *update_restrictive_policies;

		get_policies_for_relation(rel, CMD_UPDATE, user_id,
								  &update_permissive_policies,
								  &update_restrictive_policies);

		add_security_quals(rt_index,
						   update_permissive_policies,
						   update_restrictive_policies,
						   securityQuals,
						   hasSubLinks);
	}

	/*
	 * For SELECT, UPDATE and DELETE, add security quals to enforce the USING
	 * policies.  These security quals control access to existing table rows.
	 * Restrictive policies are combined together using AND, and permissive
	 * policies are combined together using OR.
	 */

	get_policies_for_relation(rel, commandType, user_id, &permissive_policies,
							  &restrictive_policies);

	if (commandType == CMD_SELECT ||
		commandType == CMD_UPDATE ||
		commandType == CMD_DELETE)
		add_security_quals(rt_index,
						   permissive_policies,
						   restrictive_policies,
						   securityQuals,
						   hasSubLinks);

	/*
	 * Similar to above, during an UPDATE or DELETE, if SELECT rights are also
	 * required (eg: when a RETURNING clause exists, or the user has provided
	 * a WHERE clause which involves columns from the relation), we collect up
	 * CMD_SELECT policies and add them via add_security_quals first.
	 *
	 * This way, we filter out any records which are not visible through an
	 * ALL or SELECT USING policy.
	 */
	if ((commandType == CMD_UPDATE || commandType == CMD_DELETE) &&
		rte->requiredPerms & ACL_SELECT)
	{
		List	   *select_permissive_policies;
		List	   *select_restrictive_policies;

		get_policies_for_relation(rel, CMD_SELECT, user_id,
								  &select_permissive_policies,
								  &select_restrictive_policies);

		add_security_quals(rt_index,
						   select_permissive_policies,
						   select_restrictive_policies,
						   securityQuals,
						   hasSubLinks);
	}

	/*
	 * For INSERT and UPDATE, add withCheckOptions to verify that any new
	 * records added are consistent with the security policies.  This will use
	 * each policy's WITH CHECK clause, or its USING clause if no explicit
	 * WITH CHECK clause is defined.
	 */
	if (commandType == CMD_INSERT || commandType == CMD_UPDATE)
	{
		/* This should be the target relation */
		Assert(rt_index == root->resultRelation);

		add_with_check_options(rel, rt_index,
							   commandType == CMD_INSERT ?
							   WCO_RLS_INSERT_CHECK : WCO_RLS_UPDATE_CHECK,
							   permissive_policies,
							   restrictive_policies,
							   withCheckOptions,
							   hasSubLinks,
							   false);

		/*
		 * Get and add ALL/SELECT policies, if SELECT rights are required for
		 * this relation (eg: when RETURNING is used).  These are added as WCO
		 * policies rather than security quals to ensure that an error is
		 * raised if a policy is violated; otherwise, we might end up silently
		 * dropping rows to be added.
		 */
		if (rte->requiredPerms & ACL_SELECT)
		{
			List	   *select_permissive_policies = NIL;
			List	   *select_restrictive_policies = NIL;

			get_policies_for_relation(rel, CMD_SELECT, user_id,
									  &select_permissive_policies,
									  &select_restrictive_policies);
			add_with_check_options(rel, rt_index,
								   commandType == CMD_INSERT ?
								   WCO_RLS_INSERT_CHECK : WCO_RLS_UPDATE_CHECK,
								   select_permissive_policies,
								   select_restrictive_policies,
								   withCheckOptions,
								   hasSubLinks,
								   true);
		}

		/*
		 * For INSERT ... ON CONFLICT DO UPDATE we need additional policy
		 * checks for the UPDATE which may be applied to the same RTE.
		 */
		if (commandType == CMD_INSERT &&
			root->onConflict && root->onConflict->action == ONCONFLICT_UPDATE)
		{
			List	   *conflict_permissive_policies;
			List	   *conflict_restrictive_policies;
			List	   *conflict_select_permissive_policies = NIL;
			List	   *conflict_select_restrictive_policies = NIL;

			/* Get the policies that apply to the auxiliary UPDATE */
			get_policies_for_relation(rel, CMD_UPDATE, user_id,
									  &conflict_permissive_policies,
									  &conflict_restrictive_policies);

			/*
			 * Enforce the USING clauses of the UPDATE policies using WCOs
			 * rather than security quals.  This ensures that an error is
			 * raised if the conflicting row cannot be updated due to RLS,
			 * rather than the change being silently dropped.
			 */
			add_with_check_options(rel, rt_index,
								   WCO_RLS_CONFLICT_CHECK,
								   conflict_permissive_policies,
								   conflict_restrictive_policies,
								   withCheckOptions,
								   hasSubLinks,
								   true);

			/*
			 * Get and add ALL/SELECT policies, as WCO_RLS_CONFLICT_CHECK WCOs
			 * to ensure they are considered when taking the UPDATE path of an
			 * INSERT .. ON CONFLICT DO UPDATE, if SELECT rights are required
			 * for this relation, also as WCO policies, again, to avoid
			 * silently dropping data.  See above.
			 */
			if (rte->requiredPerms & ACL_SELECT)
			{
				get_policies_for_relation(rel, CMD_SELECT, user_id,
										  &conflict_select_permissive_policies,
										  &conflict_select_restrictive_policies);
				add_with_check_options(rel, rt_index,
									   WCO_RLS_CONFLICT_CHECK,
									   conflict_select_permissive_policies,
									   conflict_select_restrictive_policies,
									   withCheckOptions,
									   hasSubLinks,
									   true);
			}

			/* Enforce the WITH CHECK clauses of the UPDATE policies */
			add_with_check_options(rel, rt_index,
								   WCO_RLS_UPDATE_CHECK,
								   conflict_permissive_policies,
								   conflict_restrictive_policies,
								   withCheckOptions,
								   hasSubLinks,
								   false);

			/*
			 * Add ALL/SELECT policies as WCO_RLS_UPDATE_CHECK WCOs, to ensure
			 * that the final updated row is visible when taking the UPDATE
			 * path of an INSERT .. ON CONFLICT DO UPDATE, if SELECT rights
			 * are required for this relation.
			 */
			if (rte->requiredPerms & ACL_SELECT)
				add_with_check_options(rel, rt_index,
									   WCO_RLS_UPDATE_CHECK,
									   conflict_select_permissive_policies,
									   conflict_select_restrictive_policies,
									   withCheckOptions,
									   hasSubLinks,
									   true);
		}
	}

	table_close(rel, NoLock);

	/*
	 * Copy checkAsUser to the row security quals and WithCheckOption checks,
	 * in case they contain any subqueries referring to other relations.
	 */
	setRuleCheckAsUser((Node *) *securityQuals, rte->checkAsUser);
	setRuleCheckAsUser((Node *) *withCheckOptions, rte->checkAsUser);

	/*
	 * Mark this query as having row security, so plancache can invalidate it
	 * when necessary (eg: role changes)
	 */
	*hasRowSecurity = true;

	return;
}