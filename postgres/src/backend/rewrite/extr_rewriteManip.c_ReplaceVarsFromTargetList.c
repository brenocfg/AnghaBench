#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nomatch_varno; int /*<<< orphan*/  nomatch_option; int /*<<< orphan*/ * targetlist; int /*<<< orphan*/ * target_rte; } ;
typedef  int /*<<< orphan*/  ReplaceVarsNoMatchOption ;
typedef  TYPE_1__ ReplaceVarsFromTargetList_context ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ReplaceVarsFromTargetList_callback ; 
 int /*<<< orphan*/ * replace_rte_variables (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*,int*) ; 

Node *
ReplaceVarsFromTargetList(Node *node,
						  int target_varno, int sublevels_up,
						  RangeTblEntry *target_rte,
						  List *targetlist,
						  ReplaceVarsNoMatchOption nomatch_option,
						  int nomatch_varno,
						  bool *outer_hasSubLinks)
{
	ReplaceVarsFromTargetList_context context;

	context.target_rte = target_rte;
	context.targetlist = targetlist;
	context.nomatch_option = nomatch_option;
	context.nomatch_varno = nomatch_varno;

	return replace_rte_variables(node, target_varno, sublevels_up,
								 ReplaceVarsFromTargetList_callback,
								 (void *) &context,
								 outer_hasSubLinks);
}