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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_blkbits; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,int,unsigned int) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 

__attribute__((used)) static struct buffer_head *create_page_buffers(struct page *page, struct inode *inode, unsigned int b_state)
{
	BUG_ON(!PageLocked(page));

	if (!page_has_buffers(page))
		create_empty_buffers(page, 1 << READ_ONCE(inode->i_blkbits),
				     b_state);
	return page_buffers(page);
}