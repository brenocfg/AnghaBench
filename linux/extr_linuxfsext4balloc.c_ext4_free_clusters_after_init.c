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
struct ext4_group_desc {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;

/* Variables and functions */
 int ext4_num_overhead_clusters (struct super_block*,int /*<<< orphan*/ ,struct ext4_group_desc*) ; 
 int num_clusters_in_group (struct super_block*,int /*<<< orphan*/ ) ; 

unsigned ext4_free_clusters_after_init(struct super_block *sb,
				       ext4_group_t block_group,
				       struct ext4_group_desc *gdp)
{
	return num_clusters_in_group(sb, block_group) - 
		ext4_num_overhead_clusters(sb, block_group, gdp);
}