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
struct _ore_r4w_op {int /*<<< orphan*/  (* put_page ) (void*,struct page*) ;} ;
struct __stripe_pages_2d {unsigned int data_devs; unsigned int parity; int needed; int pages_in_unit; struct __1_page_stripe* _1p_stripes; } ;
struct __1_page_stripe {int* page_is_read; int /*<<< orphan*/ * tx; scalar_t__ write_count; struct page** pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct page**,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (void*,struct page*) ; 

__attribute__((used)) static void _sp2d_reset(struct __stripe_pages_2d *sp2d,
			const struct _ore_r4w_op *r4w, void *priv)
{
	unsigned data_devs = sp2d->data_devs;
	unsigned group_width = data_devs + sp2d->parity;
	int p, c;

	if (!sp2d->needed)
		return;

	for (c = data_devs - 1; c >= 0; --c)
		for (p = sp2d->pages_in_unit - 1; p >= 0; --p) {
			struct __1_page_stripe *_1ps = &sp2d->_1p_stripes[p];

			if (_1ps->page_is_read[c]) {
				struct page *page = _1ps->pages[c];

				r4w->put_page(priv, page);
				_1ps->page_is_read[c] = false;
			}
		}

	for (p = 0; p < sp2d->pages_in_unit; p++) {
		struct __1_page_stripe *_1ps = &sp2d->_1p_stripes[p];

		memset(_1ps->pages, 0, group_width * sizeof(*_1ps->pages));
		_1ps->write_count = 0;
		_1ps->tx = NULL;
	}

	sp2d->needed = false;
}