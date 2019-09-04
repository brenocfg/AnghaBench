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
struct selinux_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int sel_make_bools (struct selinux_fs_info*) ; 
 int sel_make_classes (struct selinux_fs_info*) ; 
 int sel_make_policycap (struct selinux_fs_info*) ; 

__attribute__((used)) static int sel_make_policy_nodes(struct selinux_fs_info *fsi)
{
	int ret;

	ret = sel_make_bools(fsi);
	if (ret) {
		pr_err("SELinux: failed to load policy booleans\n");
		return ret;
	}

	ret = sel_make_classes(fsi);
	if (ret) {
		pr_err("SELinux: failed to load policy classes\n");
		return ret;
	}

	ret = sel_make_policycap(fsi);
	if (ret) {
		pr_err("SELinux: failed to load policy capabilities\n");
		return ret;
	}

	return 0;
}