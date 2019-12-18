#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  InheritanceKind ; 
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_baserels ; 
 int /*<<< orphan*/  append_rel_list ; 
 int /*<<< orphan*/  canon_pathkeys ; 
 int /*<<< orphan*/  cte_plan_ids ; 
 int /*<<< orphan*/  curOuterParams ; 
 int /*<<< orphan*/  curOuterRels ; 
 int /*<<< orphan*/  distinct_pathkeys ; 
 int /*<<< orphan*/  ec_merging_done ; 
 int /*<<< orphan*/  eq_classes ; 
 int /*<<< orphan*/  fkey_list ; 
 int /*<<< orphan*/  full_join_clauses ; 
 int /*<<< orphan*/  glob ; 
 int /*<<< orphan*/  group_pathkeys ; 
 int /*<<< orphan*/  hasHavingQual ; 
 int /*<<< orphan*/  hasJoinRTEs ; 
 int /*<<< orphan*/  hasLateralRTEs ; 
 int /*<<< orphan*/  hasPseudoConstantQuals ; 
 int /*<<< orphan*/  hasRecursion ; 
 int /*<<< orphan*/  inhTargetKind ; 
 int /*<<< orphan*/  init_plans ; 
 int /*<<< orphan*/  join_cur_level ; 
 int /*<<< orphan*/  join_info_list ; 
 int /*<<< orphan*/  join_rel_list ; 
 int /*<<< orphan*/  left_join_clauses ; 
 int /*<<< orphan*/  limit_tuples ; 
 int /*<<< orphan*/  minmax_aggs ; 
 int /*<<< orphan*/  multiexpr_params ; 
 int /*<<< orphan*/  nullable_baserels ; 
 int /*<<< orphan*/  outer_params ; 
 int /*<<< orphan*/  parse ; 
 int /*<<< orphan*/  partColsUpdated ; 
 int /*<<< orphan*/  placeholder_list ; 
 int /*<<< orphan*/  plan_params ; 
 int /*<<< orphan*/  processed_tlist ; 
 int /*<<< orphan*/  qual_security_level ; 
 int /*<<< orphan*/  query_level ; 
 int /*<<< orphan*/  query_pathkeys ; 
 int /*<<< orphan*/  right_join_clauses ; 
 int /*<<< orphan*/  rowMarks ; 
 int /*<<< orphan*/  sort_pathkeys ; 
 int /*<<< orphan*/  total_table_pages ; 
 int /*<<< orphan*/  tuple_fraction ; 
 int /*<<< orphan*/  window_pathkeys ; 
 int /*<<< orphan*/  wt_param_id ; 

__attribute__((used)) static void
_outPlannerInfo(StringInfo str, const PlannerInfo *node)
{
	WRITE_NODE_TYPE("PLANNERINFO");

	/* NB: this isn't a complete set of fields */
	WRITE_NODE_FIELD(parse);
	WRITE_NODE_FIELD(glob);
	WRITE_UINT_FIELD(query_level);
	WRITE_NODE_FIELD(plan_params);
	WRITE_BITMAPSET_FIELD(outer_params);
	WRITE_BITMAPSET_FIELD(all_baserels);
	WRITE_BITMAPSET_FIELD(nullable_baserels);
	WRITE_NODE_FIELD(join_rel_list);
	WRITE_INT_FIELD(join_cur_level);
	WRITE_NODE_FIELD(init_plans);
	WRITE_NODE_FIELD(cte_plan_ids);
	WRITE_NODE_FIELD(multiexpr_params);
	WRITE_NODE_FIELD(eq_classes);
	WRITE_BOOL_FIELD(ec_merging_done);
	WRITE_NODE_FIELD(canon_pathkeys);
	WRITE_NODE_FIELD(left_join_clauses);
	WRITE_NODE_FIELD(right_join_clauses);
	WRITE_NODE_FIELD(full_join_clauses);
	WRITE_NODE_FIELD(join_info_list);
	WRITE_NODE_FIELD(append_rel_list);
	WRITE_NODE_FIELD(rowMarks);
	WRITE_NODE_FIELD(placeholder_list);
	WRITE_NODE_FIELD(fkey_list);
	WRITE_NODE_FIELD(query_pathkeys);
	WRITE_NODE_FIELD(group_pathkeys);
	WRITE_NODE_FIELD(window_pathkeys);
	WRITE_NODE_FIELD(distinct_pathkeys);
	WRITE_NODE_FIELD(sort_pathkeys);
	WRITE_NODE_FIELD(processed_tlist);
	WRITE_NODE_FIELD(minmax_aggs);
	WRITE_FLOAT_FIELD(total_table_pages, "%.0f");
	WRITE_FLOAT_FIELD(tuple_fraction, "%.4f");
	WRITE_FLOAT_FIELD(limit_tuples, "%.0f");
	WRITE_UINT_FIELD(qual_security_level);
	WRITE_ENUM_FIELD(inhTargetKind, InheritanceKind);
	WRITE_BOOL_FIELD(hasJoinRTEs);
	WRITE_BOOL_FIELD(hasLateralRTEs);
	WRITE_BOOL_FIELD(hasHavingQual);
	WRITE_BOOL_FIELD(hasPseudoConstantQuals);
	WRITE_BOOL_FIELD(hasRecursion);
	WRITE_INT_FIELD(wt_param_id);
	WRITE_BITMAPSET_FIELD(curOuterRels);
	WRITE_NODE_FIELD(curOuterParams);
	WRITE_BOOL_FIELD(partColsUpdated);
}