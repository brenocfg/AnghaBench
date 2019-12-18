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
struct dsa_switch_tree {int /*<<< orphan*/ ** ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_tree_put (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  dsa_tree_teardown (struct dsa_switch_tree*) ; 

__attribute__((used)) static void dsa_tree_remove_switch(struct dsa_switch_tree *dst,
				   unsigned int index)
{
	dsa_tree_teardown(dst);

	dst->ds[index] = NULL;
	dsa_tree_put(dst);
}