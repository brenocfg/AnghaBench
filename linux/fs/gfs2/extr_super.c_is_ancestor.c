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
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ROOT (struct dentry const*) ; 

__attribute__((used)) static int is_ancestor(const struct dentry *d1, const struct dentry *d2)
{
	do {
		if (d1 == d2)
			return 1;
		d1 = d1->d_parent;
	} while (!IS_ROOT(d1));
	return 0;
}