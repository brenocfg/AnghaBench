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
typedef  unsigned int u32 ;
struct super_block {int dummy; } ;
struct TYPE_2__ {unsigned int s_clustersize_bits; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned int ocfs2_page_index_to_clusters(struct super_block *sb,
							unsigned long pg_index)
{
	u32 clusters = pg_index;
	unsigned int cbits = OCFS2_SB(sb)->s_clustersize_bits;

	if (unlikely(PAGE_SHIFT > cbits))
		clusters = pg_index << (PAGE_SHIFT - cbits);
	else if (PAGE_SHIFT < cbits)
		clusters = pg_index >> (cbits - PAGE_SHIFT);

	return clusters;
}