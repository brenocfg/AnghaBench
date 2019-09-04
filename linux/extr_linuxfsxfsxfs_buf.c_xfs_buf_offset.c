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
struct xfs_buf {void* b_addr; struct page** b_pages; scalar_t__ b_offset; } ;
struct page {int dummy; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 void* page_address (struct page*) ; 

void *
xfs_buf_offset(
	struct xfs_buf		*bp,
	size_t			offset)
{
	struct page		*page;

	if (bp->b_addr)
		return bp->b_addr + offset;

	offset += bp->b_offset;
	page = bp->b_pages[offset >> PAGE_SHIFT];
	return page_address(page) + (offset & (PAGE_SIZE-1));
}