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
typedef  int /*<<< orphan*/  Plan ;

/* Variables and functions */
#define  T_Append 139 
#define  T_Hash 138 
#define  T_Limit 137 
#define  T_LockRows 136 
#define  T_Material 135 
#define  T_MergeAppend 134 
#define  T_ModifyTable 133 
#define  T_ProjectSet 132 
#define  T_RecursiveUnion 131 
#define  T_SetOp 130 
#define  T_Sort 129 
#define  T_Unique 128 
 int nodeTag (int /*<<< orphan*/ *) ; 

bool
is_projection_capable_plan(Plan *plan)
{
	/* Most plan types can project, so just list the ones that can't */
	switch (nodeTag(plan))
	{
		case T_Hash:
		case T_Material:
		case T_Sort:
		case T_Unique:
		case T_SetOp:
		case T_LockRows:
		case T_Limit:
		case T_ModifyTable:
		case T_Append:
		case T_MergeAppend:
		case T_RecursiveUnion:
			return false;
		case T_ProjectSet:

			/*
			 * Although ProjectSet certainly projects, say "no" because we
			 * don't want the planner to randomly replace its tlist with
			 * something else; the SRFs have to stay at top level.  This might
			 * get relaxed later.
			 */
			return false;
		default:
			break;
	}
	return true;
}