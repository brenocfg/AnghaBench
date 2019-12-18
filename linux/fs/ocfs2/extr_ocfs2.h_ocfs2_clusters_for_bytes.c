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
struct super_block {int dummy; } ;
struct TYPE_2__ {int s_clustersize_bits; int s_clustersize; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_SB (struct super_block*) ; 

__attribute__((used)) static inline unsigned int ocfs2_clusters_for_bytes(struct super_block *sb,
						    u64 bytes)
{
	int cl_bits = OCFS2_SB(sb)->s_clustersize_bits;
	unsigned int clusters;

	bytes += OCFS2_SB(sb)->s_clustersize - 1;
	/* OCFS2 just cannot have enough clusters to overflow this */
	clusters = (unsigned int)(bytes >> cl_bits);

	return clusters;
}