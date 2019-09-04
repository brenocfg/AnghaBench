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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int s_blocksize_bits; } ;
struct TYPE_2__ {int s_clustersize_bits; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_SB (struct super_block*) ; 

__attribute__((used)) static inline u32 ocfs2_clusters_for_blocks(struct super_block *sb,
		u64 blocks)
{
	int b_to_c_bits = OCFS2_SB(sb)->s_clustersize_bits -
			sb->s_blocksize_bits;

	blocks += (1 << b_to_c_bits) - 1;
	return (u32)(blocks >> b_to_c_bits);
}