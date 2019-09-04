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
struct dsa_switch_tree {int dummy; } ;
struct dsa_switch {struct dsa_switch_tree* dst; } ;

/* Variables and functions */
 int dsa_tree_add_switch (struct dsa_switch_tree*,struct dsa_switch*) ; 

__attribute__((used)) static int dsa_switch_add(struct dsa_switch *ds)
{
	struct dsa_switch_tree *dst = ds->dst;

	return dsa_tree_add_switch(dst, ds);
}