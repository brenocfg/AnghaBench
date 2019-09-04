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
struct the_nilfs {int /*<<< orphan*/  ns_blocksize; int /*<<< orphan*/  ns_bdev; } ;
struct nilfs_segment_summary {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct buffer_head* __bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buffer_head *
nilfs_read_log_header(struct the_nilfs *nilfs, sector_t start_blocknr,
		      struct nilfs_segment_summary **sum)
{
	struct buffer_head *bh_sum;

	bh_sum = __bread(nilfs->ns_bdev, start_blocknr, nilfs->ns_blocksize);
	if (bh_sum)
		*sum = (struct nilfs_segment_summary *)bh_sum->b_data;
	return bh_sum;
}