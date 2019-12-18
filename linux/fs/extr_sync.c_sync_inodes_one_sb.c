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
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sync_inodes_sb (struct super_block*) ; 

__attribute__((used)) static void sync_inodes_one_sb(struct super_block *sb, void *arg)
{
	if (!sb_rdonly(sb))
		sync_inodes_sb(sb);
}