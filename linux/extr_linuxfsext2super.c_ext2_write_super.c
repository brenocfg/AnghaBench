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

/* Variables and functions */
 int /*<<< orphan*/  ext2_sync_fs (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

__attribute__((used)) static void ext2_write_super(struct super_block *sb)
{
	if (!sb_rdonly(sb))
		ext2_sync_fs(sb, 1);
}