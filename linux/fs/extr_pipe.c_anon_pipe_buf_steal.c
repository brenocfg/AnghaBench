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
struct pipe_inode_info {int dummy; } ;
struct pipe_buffer {struct page* page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __SetPageLocked (struct page*) ; 
 int /*<<< orphan*/  memcg_kmem_uncharge (struct page*,int /*<<< orphan*/ ) ; 
 int page_count (struct page*) ; 

__attribute__((used)) static int anon_pipe_buf_steal(struct pipe_inode_info *pipe,
			       struct pipe_buffer *buf)
{
	struct page *page = buf->page;

	if (page_count(page) == 1) {
		memcg_kmem_uncharge(page, 0);
		__SetPageLocked(page);
		return 0;
	}
	return 1;
}