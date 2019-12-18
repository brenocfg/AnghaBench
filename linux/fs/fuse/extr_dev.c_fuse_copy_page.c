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
struct fuse_copy_state {scalar_t__ write; scalar_t__ move_pages; int /*<<< orphan*/  len; scalar_t__ pipebufs; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  clear_highpage (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 unsigned int fuse_copy_do (struct fuse_copy_state*,void**,unsigned int*) ; 
 int fuse_copy_fill (struct fuse_copy_state*) ; 
 int fuse_ref_page (struct fuse_copy_state*,struct page*,unsigned int,unsigned int) ; 
 int fuse_try_move_page (struct fuse_copy_state*,struct page**) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 

__attribute__((used)) static int fuse_copy_page(struct fuse_copy_state *cs, struct page **pagep,
			  unsigned offset, unsigned count, int zeroing)
{
	int err;
	struct page *page = *pagep;

	if (page && zeroing && count < PAGE_SIZE)
		clear_highpage(page);

	while (count) {
		if (cs->write && cs->pipebufs && page) {
			return fuse_ref_page(cs, page, offset, count);
		} else if (!cs->len) {
			if (cs->move_pages && page &&
			    offset == 0 && count == PAGE_SIZE) {
				err = fuse_try_move_page(cs, pagep);
				if (err <= 0)
					return err;
			} else {
				err = fuse_copy_fill(cs);
				if (err)
					return err;
			}
		}
		if (page) {
			void *mapaddr = kmap_atomic(page);
			void *buf = mapaddr + offset;
			offset += fuse_copy_do(cs, &buf, &count);
			kunmap_atomic(mapaddr);
		} else
			offset += fuse_copy_do(cs, NULL, &count);
	}
	if (page && !cs->write)
		flush_dcache_page(page);
	return 0;
}