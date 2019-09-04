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
struct the_nilfs {int ns_first_data_block; scalar_t__ ns_blocks_per_segment; } ;
typedef  int sector_t ;
typedef  int __u64 ;

/* Variables and functions */

__attribute__((used)) static inline sector_t
nilfs_get_segment_start_blocknr(struct the_nilfs *nilfs, __u64 segnum)
{
	return (segnum == 0) ? nilfs->ns_first_data_block :
		(sector_t)nilfs->ns_blocks_per_segment * segnum;
}