#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long b_offset; int b_page_count; void* b_length; void* b_io_length; int /*<<< orphan*/ * b_pages; void* b_addr; } ;
typedef  TYPE_1__ xfs_buf_t ;

/* Variables and functions */
 void* BTOBB (size_t) ; 
 size_t PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  _xfs_buf_free_pages (TYPE_1__*) ; 
 int _xfs_buf_get_pages (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mem_to_page (void*) ; 

int
xfs_buf_associate_memory(
	xfs_buf_t		*bp,
	void			*mem,
	size_t			len)
{
	int			rval;
	int			i = 0;
	unsigned long		pageaddr;
	unsigned long		offset;
	size_t			buflen;
	int			page_count;

	pageaddr = (unsigned long)mem & PAGE_MASK;
	offset = (unsigned long)mem - pageaddr;
	buflen = PAGE_ALIGN(len + offset);
	page_count = buflen >> PAGE_SHIFT;

	/* Free any previous set of page pointers */
	if (bp->b_pages)
		_xfs_buf_free_pages(bp);

	bp->b_pages = NULL;
	bp->b_addr = mem;

	rval = _xfs_buf_get_pages(bp, page_count);
	if (rval)
		return rval;

	bp->b_offset = offset;

	for (i = 0; i < bp->b_page_count; i++) {
		bp->b_pages[i] = mem_to_page((void *)pageaddr);
		pageaddr += PAGE_SIZE;
	}

	bp->b_io_length = BTOBB(len);
	bp->b_length = BTOBB(buflen);

	return 0;
}