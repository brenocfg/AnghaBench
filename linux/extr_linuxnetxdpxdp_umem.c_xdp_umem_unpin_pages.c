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
struct xdp_umem {unsigned int npgs; struct page** pgs; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 

__attribute__((used)) static void xdp_umem_unpin_pages(struct xdp_umem *umem)
{
	unsigned int i;

	for (i = 0; i < umem->npgs; i++) {
		struct page *page = umem->pgs[i];

		set_page_dirty_lock(page);
		put_page(page);
	}

	kfree(umem->pgs);
	umem->pgs = NULL;
}