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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  THREADNODE ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_thread_tree_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*,char*) ; 

__attribute__((used)) static int build_thread_tree(THREADNODE *top, zval **tree)
{
	long numNodes = 0;
	char buf[25];

	array_init(*tree);

	build_thread_tree_helper(top, *tree, &numNodes, buf);

	return SUCCESS;
}