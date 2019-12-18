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
struct super_block {int /*<<< orphan*/  s_flags; int /*<<< orphan*/ * s_d_op; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dir_ops; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SB_NOATIME ; 
 int /*<<< orphan*/  msdos_dentry_operations ; 
 int /*<<< orphan*/  msdos_dir_inode_operations ; 

__attribute__((used)) static void setup(struct super_block *sb)
{
	MSDOS_SB(sb)->dir_ops = &msdos_dir_inode_operations;
	sb->s_d_op = &msdos_dentry_operations;
	sb->s_flags |= SB_NOATIME;
}