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
struct proc_dir_entry {int /*<<< orphan*/  parent; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_proc_subtree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void proc_remove(struct proc_dir_entry *de)
{
	if (de)
		remove_proc_subtree(de->name, de->parent);
}