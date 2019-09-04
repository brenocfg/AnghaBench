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
struct dsa_switch_tree {int /*<<< orphan*/ * cpu_dp; } ;

/* Variables and functions */

__attribute__((used)) static void dsa_tree_teardown_default_cpu(struct dsa_switch_tree *dst)
{
	/* DSA currently only supports a single CPU port */
	dst->cpu_dp = NULL;
}