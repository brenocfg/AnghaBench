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
typedef  int /*<<< orphan*/  RelOptInfo ;

/* Variables and functions */
 int /*<<< orphan*/  RTEKind ; 
 int /*<<< orphan*/  RelOptKind ; 
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allvisfrac ; 
 int /*<<< orphan*/  baserestrict_min_security ; 
 int /*<<< orphan*/  baserestrictinfo ; 
 int /*<<< orphan*/  cheapest_parameterized_paths ; 
 int /*<<< orphan*/  cheapest_startup_path ; 
 int /*<<< orphan*/  cheapest_total_path ; 
 int /*<<< orphan*/  cheapest_unique_path ; 
 int /*<<< orphan*/  consider_parallel ; 
 int /*<<< orphan*/  consider_param_startup ; 
 int /*<<< orphan*/  consider_partitionwise_join ; 
 int /*<<< orphan*/  consider_startup ; 
 int /*<<< orphan*/  direct_lateral_relids ; 
 int /*<<< orphan*/  eclass_indexes ; 
 int /*<<< orphan*/  has_eclass_joins ; 
 int /*<<< orphan*/  indexlist ; 
 int /*<<< orphan*/  joininfo ; 
 int /*<<< orphan*/  lateral_referencers ; 
 int /*<<< orphan*/  lateral_relids ; 
 int /*<<< orphan*/  lateral_vars ; 
 int /*<<< orphan*/  max_attr ; 
 int /*<<< orphan*/  min_attr ; 
 int /*<<< orphan*/  pages ; 
 int /*<<< orphan*/  partial_pathlist ; 
 int /*<<< orphan*/  partitioned_child_rels ; 
 int /*<<< orphan*/  pathlist ; 
 int /*<<< orphan*/  ppilist ; 
 int /*<<< orphan*/  rel_parallel_workers ; 
 int /*<<< orphan*/  relid ; 
 int /*<<< orphan*/  relids ; 
 int /*<<< orphan*/  reloptkind ; 
 int /*<<< orphan*/  reltablespace ; 
 int /*<<< orphan*/  reltarget ; 
 int /*<<< orphan*/  rows ; 
 int /*<<< orphan*/  rtekind ; 
 int /*<<< orphan*/  serverid ; 
 int /*<<< orphan*/  statlist ; 
 int /*<<< orphan*/  subplan_params ; 
 int /*<<< orphan*/  subroot ; 
 int /*<<< orphan*/  top_parent_relids ; 
 int /*<<< orphan*/  tuples ; 
 int /*<<< orphan*/  userid ; 
 int /*<<< orphan*/  useridiscurrent ; 

__attribute__((used)) static void
_outRelOptInfo(StringInfo str, const RelOptInfo *node)
{
	WRITE_NODE_TYPE("RELOPTINFO");

	/* NB: this isn't a complete set of fields */
	WRITE_ENUM_FIELD(reloptkind, RelOptKind);
	WRITE_BITMAPSET_FIELD(relids);
	WRITE_FLOAT_FIELD(rows, "%.0f");
	WRITE_BOOL_FIELD(consider_startup);
	WRITE_BOOL_FIELD(consider_param_startup);
	WRITE_BOOL_FIELD(consider_parallel);
	WRITE_NODE_FIELD(reltarget);
	WRITE_NODE_FIELD(pathlist);
	WRITE_NODE_FIELD(ppilist);
	WRITE_NODE_FIELD(partial_pathlist);
	WRITE_NODE_FIELD(cheapest_startup_path);
	WRITE_NODE_FIELD(cheapest_total_path);
	WRITE_NODE_FIELD(cheapest_unique_path);
	WRITE_NODE_FIELD(cheapest_parameterized_paths);
	WRITE_BITMAPSET_FIELD(direct_lateral_relids);
	WRITE_BITMAPSET_FIELD(lateral_relids);
	WRITE_UINT_FIELD(relid);
	WRITE_OID_FIELD(reltablespace);
	WRITE_ENUM_FIELD(rtekind, RTEKind);
	WRITE_INT_FIELD(min_attr);
	WRITE_INT_FIELD(max_attr);
	WRITE_NODE_FIELD(lateral_vars);
	WRITE_BITMAPSET_FIELD(lateral_referencers);
	WRITE_NODE_FIELD(indexlist);
	WRITE_NODE_FIELD(statlist);
	WRITE_UINT_FIELD(pages);
	WRITE_FLOAT_FIELD(tuples, "%.0f");
	WRITE_FLOAT_FIELD(allvisfrac, "%.6f");
	WRITE_BITMAPSET_FIELD(eclass_indexes);
	WRITE_NODE_FIELD(subroot);
	WRITE_NODE_FIELD(subplan_params);
	WRITE_INT_FIELD(rel_parallel_workers);
	WRITE_OID_FIELD(serverid);
	WRITE_OID_FIELD(userid);
	WRITE_BOOL_FIELD(useridiscurrent);
	/* we don't try to print fdwroutine or fdw_private */
	/* can't print unique_for_rels/non_unique_for_rels; BMSes aren't Nodes */
	WRITE_NODE_FIELD(baserestrictinfo);
	WRITE_UINT_FIELD(baserestrict_min_security);
	WRITE_NODE_FIELD(joininfo);
	WRITE_BOOL_FIELD(has_eclass_joins);
	WRITE_BOOL_FIELD(consider_partitionwise_join);
	WRITE_BITMAPSET_FIELD(top_parent_relids);
	WRITE_NODE_FIELD(partitioned_child_rels);
}