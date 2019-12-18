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

/* Variables and functions */
 int /*<<< orphan*/ * proc_info_root ; 
 int /*<<< orphan*/  proc_info_root_name ; 
 int /*<<< orphan*/ * proc_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int reiserfs_proc_info_global_init(void)
{
	if (proc_info_root == NULL) {
		proc_info_root = proc_mkdir(proc_info_root_name, NULL);
		if (!proc_info_root) {
			reiserfs_warning(NULL, "cannot create /proc/%s",
					 proc_info_root_name);
			return 1;
		}
	}
	return 0;
}