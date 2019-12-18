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
struct nilfs_write_info {int /*<<< orphan*/  blocknr; scalar_t__ end; scalar_t__ start; int /*<<< orphan*/  rest_blocks; int /*<<< orphan*/  max_pages; int /*<<< orphan*/  nr_vecs; int /*<<< orphan*/ * bio; } ;
struct TYPE_2__ {int /*<<< orphan*/  nblocks; } ;
struct nilfs_segment_buffer {int /*<<< orphan*/  sb_pseg_start; TYPE_1__ sb_sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_segbuf_prepare_write(struct nilfs_segment_buffer *segbuf,
				       struct nilfs_write_info *wi)
{
	wi->bio = NULL;
	wi->rest_blocks = segbuf->sb_sum.nblocks;
	wi->max_pages = BIO_MAX_PAGES;
	wi->nr_vecs = min(wi->max_pages, wi->rest_blocks);
	wi->start = wi->end = 0;
	wi->blocknr = segbuf->sb_pseg_start;
}