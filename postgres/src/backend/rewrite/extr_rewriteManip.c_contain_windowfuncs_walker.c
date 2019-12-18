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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindowFunc ; 
 int expression_tree_walker (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 

__attribute__((used)) static bool
contain_windowfuncs_walker(Node *node, void *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, WindowFunc))
		return true;			/* abort the tree traversal and return true */
	/* Mustn't recurse into subselects */
	return expression_tree_walker(node, contain_windowfuncs_walker,
								  (void *) context);
}