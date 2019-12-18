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
struct super_block {int dummy; } ;
struct pts_fs_info {int /*<<< orphan*/  allocated_ptys; } ;

/* Variables and functions */
 struct pts_fs_info* DEVPTS_SB (struct super_block*) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pts_fs_info*) ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 

__attribute__((used)) static void devpts_kill_sb(struct super_block *sb)
{
	struct pts_fs_info *fsi = DEVPTS_SB(sb);

	if (fsi)
		ida_destroy(&fsi->allocated_ptys);
	kfree(fsi);
	kill_litter_super(sb);
}