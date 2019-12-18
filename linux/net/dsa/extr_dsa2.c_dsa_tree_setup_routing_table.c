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
struct dsa_switch_tree {struct dsa_switch** ds; } ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int DSA_MAX_SWITCHES ; 
 int dsa_switch_setup_routing_table (struct dsa_switch*) ; 

__attribute__((used)) static bool dsa_tree_setup_routing_table(struct dsa_switch_tree *dst)
{
	struct dsa_switch *ds;
	bool complete = true;
	int device;

	for (device = 0; device < DSA_MAX_SWITCHES; device++) {
		ds = dst->ds[device];
		if (!ds)
			continue;

		complete = dsa_switch_setup_routing_table(ds);
		if (!complete)
			break;
	}

	return complete;
}