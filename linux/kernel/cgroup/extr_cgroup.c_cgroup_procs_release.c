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
struct kernfs_open_file {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_task_iter_end (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static void cgroup_procs_release(struct kernfs_open_file *of)
{
	if (of->priv) {
		css_task_iter_end(of->priv);
		kfree(of->priv);
	}
}