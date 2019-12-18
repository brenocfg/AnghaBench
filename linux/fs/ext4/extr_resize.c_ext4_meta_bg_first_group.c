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
typedef  int ext4_group_t ;

/* Variables and functions */
 int EXT4_DESC_PER_BLOCK_BITS (struct super_block*) ; 

__attribute__((used)) static ext4_group_t ext4_meta_bg_first_group(struct super_block *sb,
					     ext4_group_t group) {
	return (group >> EXT4_DESC_PER_BLOCK_BITS(sb)) <<
	       EXT4_DESC_PER_BLOCK_BITS(sb);
}