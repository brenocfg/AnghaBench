#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/ * s_d_op; } ;
struct TYPE_3__ {char name_check; } ;
struct TYPE_4__ {TYPE_1__ options; int /*<<< orphan*/ * dir_ops; } ;

/* Variables and functions */
 TYPE_2__* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  vfat_ci_dentry_ops ; 
 int /*<<< orphan*/  vfat_dentry_ops ; 
 int /*<<< orphan*/  vfat_dir_inode_operations ; 

__attribute__((used)) static void setup(struct super_block *sb)
{
	MSDOS_SB(sb)->dir_ops = &vfat_dir_inode_operations;
	if (MSDOS_SB(sb)->options.name_check != 's')
		sb->s_d_op = &vfat_ci_dentry_ops;
	else
		sb->s_d_op = &vfat_dentry_ops;
}