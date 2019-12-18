#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {long num; struct TYPE_3__* branch; struct TYPE_3__* next; } ;
typedef  TYPE_1__ THREADNODE ;

/* Variables and functions */
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 

__attribute__((used)) static void build_thread_tree_helper(THREADNODE *cur, zval *tree, long *numNodes, char *buf)
{
	unsigned long thisNode = *numNodes;

	/* define "#.num" */
	snprintf(buf, 25, "%ld.num", thisNode);

	add_assoc_long(tree, buf, cur->num);

	snprintf(buf, 25, "%ld.next", thisNode);
	if(cur->next) {
		(*numNodes)++;
		add_assoc_long(tree, buf, *numNodes);
		build_thread_tree_helper(cur->next, tree, numNodes, buf);
	} else { /* "null pointer" */
		add_assoc_long(tree, buf, 0);
	}

	snprintf(buf, 25, "%ld.branch", thisNode);
	if(cur->branch) {
		(*numNodes)++;
		add_assoc_long(tree, buf, *numNodes);
		build_thread_tree_helper(cur->branch, tree, numNodes, buf);
	} else { /* "null pointer" */
		add_assoc_long(tree, buf, 0);
	}
}