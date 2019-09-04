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
struct super_block {int dummy; } ;
struct TYPE_2__ {unsigned int s_log2sharesize; } ;

/* Variables and functions */
 TYPE_1__* ADFS_SB (struct super_block*) ; 
 int adfs_map_lookup (struct super_block*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline int
__adfs_block_map(struct super_block *sb, unsigned int object_id,
		 unsigned int block)
{
	if (object_id & 255) {
		unsigned int off;

		off = (object_id & 255) - 1;
		block += off << ADFS_SB(sb)->s_log2sharesize;
	}

	return adfs_map_lookup(sb, object_id >> 8, block);
}