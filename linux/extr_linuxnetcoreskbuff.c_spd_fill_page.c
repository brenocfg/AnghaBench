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
struct splice_pipe_desc {int nr_pages; TYPE_1__* partial; struct page** pages; } ;
struct sock {int dummy; } ;
struct pipe_inode_info {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {unsigned int len; unsigned int offset; } ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct page* linear_to_page (struct page*,unsigned int*,unsigned int*,struct sock*) ; 
 scalar_t__ spd_can_coalesce (struct splice_pipe_desc*,struct page*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool spd_fill_page(struct splice_pipe_desc *spd,
			  struct pipe_inode_info *pipe, struct page *page,
			  unsigned int *len, unsigned int offset,
			  bool linear,
			  struct sock *sk)
{
	if (unlikely(spd->nr_pages == MAX_SKB_FRAGS))
		return true;

	if (linear) {
		page = linear_to_page(page, len, &offset, sk);
		if (!page)
			return true;
	}
	if (spd_can_coalesce(spd, page, offset)) {
		spd->partial[spd->nr_pages - 1].len += *len;
		return false;
	}
	get_page(page);
	spd->pages[spd->nr_pages] = page;
	spd->partial[spd->nr_pages].len = *len;
	spd->partial[spd->nr_pages].offset = offset;
	spd->nr_pages++;

	return false;
}