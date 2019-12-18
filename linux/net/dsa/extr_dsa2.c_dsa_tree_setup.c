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
 int EEXIST ; 
 int dsa_tree_setup_default_cpu (struct dsa_switch_tree*) ; 
 int dsa_tree_setup_master (struct dsa_switch_tree*) ; 
 int dsa_tree_setup_routing_table (struct dsa_switch_tree*) ; 
 int dsa_tree_setup_switches (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  dsa_tree_teardown_default_cpu (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  dsa_tree_teardown_switches (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_tree_setup(struct dsa_switch_tree *dst)
{
	bool complete;
	int err;

	if (dst->setup) {
		pr_err("DSA: tree %d already setup! Disjoint trees?\n",
		       dst->index);
		return -EEXIST;
	}

	complete = dsa_tree_setup_routing_table(dst);
	if (!complete)
		return 0;

	err = dsa_tree_setup_default_cpu(dst);
	if (err)
		return err;

	err = dsa_tree_setup_switches(dst);
	if (err)
		goto teardown_default_cpu;

	err = dsa_tree_setup_master(dst);
	if (err)
		goto teardown_switches;

	dst->setup = true;

	pr_info("DSA: tree %d setup\n", dst->index);

	return 0;

teardown_switches:
	dsa_tree_teardown_switches(dst);
teardown_default_cpu:
	dsa_tree_teardown_default_cpu(dst);

	return err;
}