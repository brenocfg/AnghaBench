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
struct super_block {TYPE_1__* s_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync_fs ) (struct super_block*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int) ; 

__attribute__((used)) static void sync_fs_one_sb(struct super_block *sb, void *arg)
{
	if (!sb_rdonly(sb) && sb->s_op->sync_fs)
		sb->s_op->sync_fs(sb, *(int *)arg);
}