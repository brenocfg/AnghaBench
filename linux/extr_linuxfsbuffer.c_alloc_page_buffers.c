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
struct mem_cgroup {int dummy; } ;
struct buffer_head {int b_blocknr; unsigned long b_size; struct buffer_head* b_this_page; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_NOFS ; 
 long PAGE_SIZE ; 
 int __GFP_ACCOUNT ; 
 int __GFP_NOFAIL ; 
 struct buffer_head* alloc_buffer_head (int) ; 
 int /*<<< orphan*/  free_buffer_head (struct buffer_head*) ; 
 struct mem_cgroup* get_mem_cgroup_from_page (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_put (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memalloc_unuse_memcg () ; 
 int /*<<< orphan*/  memalloc_use_memcg (struct mem_cgroup*) ; 
 int /*<<< orphan*/  set_bh_page (struct buffer_head*,struct page*,long) ; 

struct buffer_head *alloc_page_buffers(struct page *page, unsigned long size,
		bool retry)
{
	struct buffer_head *bh, *head;
	gfp_t gfp = GFP_NOFS | __GFP_ACCOUNT;
	long offset;
	struct mem_cgroup *memcg;

	if (retry)
		gfp |= __GFP_NOFAIL;

	memcg = get_mem_cgroup_from_page(page);
	memalloc_use_memcg(memcg);

	head = NULL;
	offset = PAGE_SIZE;
	while ((offset -= size) >= 0) {
		bh = alloc_buffer_head(gfp);
		if (!bh)
			goto no_grow;

		bh->b_this_page = head;
		bh->b_blocknr = -1;
		head = bh;

		bh->b_size = size;

		/* Link the buffer to its page */
		set_bh_page(bh, page, offset);
	}
out:
	memalloc_unuse_memcg();
	mem_cgroup_put(memcg);
	return head;
/*
 * In case anything failed, we just free everything we got.
 */
no_grow:
	if (head) {
		do {
			bh = head;
			head = head->b_this_page;
			free_buffer_head(bh);
		} while (head);
	}

	goto out;
}