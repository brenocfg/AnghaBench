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
struct dsa_switch_tree {int setup; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_tree_teardown_default_cpu (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  dsa_tree_teardown_master (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  dsa_tree_teardown_switches (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsa_tree_teardown(struct dsa_switch_tree *dst)
{
	if (!dst->setup)
		return;

	dsa_tree_teardown_master(dst);

	dsa_tree_teardown_switches(dst);

	dsa_tree_teardown_default_cpu(dst);

	pr_info("DSA: tree %d torn down\n", dst->index);

	dst->setup = false;
}