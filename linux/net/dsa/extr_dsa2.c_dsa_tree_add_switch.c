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
struct dsa_switch {unsigned int index; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dsa_tree_get (struct dsa_switch_tree*) ; 
 int /*<<< orphan*/  dsa_tree_put (struct dsa_switch_tree*) ; 
 int dsa_tree_setup (struct dsa_switch_tree*) ; 

__attribute__((used)) static int dsa_tree_add_switch(struct dsa_switch_tree *dst,
			       struct dsa_switch *ds)
{
	unsigned int index = ds->index;
	int err;

	if (dst->ds[index])
		return -EBUSY;

	dsa_tree_get(dst);
	dst->ds[index] = ds;

	err = dsa_tree_setup(dst);
	if (err) {
		dst->ds[index] = NULL;
		dsa_tree_put(dst);
	}

	return err;
}