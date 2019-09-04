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
struct ext4_buddy {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int ext4_mb_load_buddy_gfp (struct super_block*,int /*<<< orphan*/ ,struct ext4_buddy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_mb_load_buddy(struct super_block *sb, ext4_group_t group,
			      struct ext4_buddy *e4b)
{
	return ext4_mb_load_buddy_gfp(sb, group, e4b, GFP_NOFS);
}