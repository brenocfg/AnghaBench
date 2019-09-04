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
struct xfs_buf {size_t b_length; size_t b_io_length; int b_map_count; TYPE_1__* b_maps; void* b_bn; int /*<<< orphan*/ * b_addr; scalar_t__ b_page_count; int /*<<< orphan*/ * b_pages; } ;
struct TYPE_2__ {size_t bm_len; void* bm_bn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* XFS_BUF_DADDR_NULL ; 
 int /*<<< orphan*/  _xfs_buf_free_pages (struct xfs_buf*) ; 

void
xfs_buf_set_empty(
	struct xfs_buf		*bp,
	size_t			numblks)
{
	if (bp->b_pages)
		_xfs_buf_free_pages(bp);

	bp->b_pages = NULL;
	bp->b_page_count = 0;
	bp->b_addr = NULL;
	bp->b_length = numblks;
	bp->b_io_length = numblks;

	ASSERT(bp->b_map_count == 1);
	bp->b_bn = XFS_BUF_DADDR_NULL;
	bp->b_maps[0].bm_bn = XFS_BUF_DADDR_NULL;
	bp->b_maps[0].bm_len = bp->b_length;
}