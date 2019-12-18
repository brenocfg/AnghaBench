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
struct cgroup_root {int /*<<< orphan*/  cgroup_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cgroup_root*) ; 

void cgroup_free_root(struct cgroup_root *root)
{
	if (root) {
		idr_destroy(&root->cgroup_idr);
		kfree(root);
	}
}