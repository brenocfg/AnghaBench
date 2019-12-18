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
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int __xlate_proc_name (char const*,struct proc_dir_entry**,char const**) ; 
 int /*<<< orphan*/  proc_subdir_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xlate_proc_name(const char *name, struct proc_dir_entry **ret,
			   const char **residual)
{
	int rv;

	read_lock(&proc_subdir_lock);
	rv = __xlate_proc_name(name, ret, residual);
	read_unlock(&proc_subdir_lock);
	return rv;
}