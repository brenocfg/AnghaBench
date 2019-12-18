#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ selinux_policycap_cgroupseclabel () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int selinux_is_genfs_special_handling(struct super_block *sb)
{
	/* Special handling. Genfs but also in-core setxattr handler */
	return	!strcmp(sb->s_type->name, "sysfs") ||
		!strcmp(sb->s_type->name, "pstore") ||
		!strcmp(sb->s_type->name, "debugfs") ||
		!strcmp(sb->s_type->name, "tracefs") ||
		!strcmp(sb->s_type->name, "rootfs") ||
		(selinux_policycap_cgroupseclabel() &&
		 (!strcmp(sb->s_type->name, "cgroup") ||
		  !strcmp(sb->s_type->name, "cgroup2")));
}