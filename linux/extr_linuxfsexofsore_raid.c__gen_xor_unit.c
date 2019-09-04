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
struct __stripe_pages_2d {int parity; unsigned int pages_in_unit; size_t data_devs; struct __1_page_stripe* _1p_stripes; } ;
struct __1_page_stripe {int /*<<< orphan*/  tx; int /*<<< orphan*/  submit; int /*<<< orphan*/ * pages; scalar_t__ scribble; int /*<<< orphan*/  write_count; } ;
typedef  int /*<<< orphan*/  addr_conv_t ;

/* Variables and functions */
 unsigned int ASYNC_TX_ACK ; 
 unsigned int ASYNC_TX_XOR_ZERO_DST ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  async_gen_syndrome (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_tx_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_async_submit (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _gen_xor_unit(struct __stripe_pages_2d *sp2d)
{
	unsigned p;
	unsigned tx_flags = ASYNC_TX_ACK;

	if (sp2d->parity == 1)
		tx_flags |= ASYNC_TX_XOR_ZERO_DST;

	for (p = 0; p < sp2d->pages_in_unit; p++) {
		struct __1_page_stripe *_1ps = &sp2d->_1p_stripes[p];

		if (!_1ps->write_count)
			continue;

		init_async_submit(&_1ps->submit, tx_flags,
			NULL, NULL, NULL, (addr_conv_t *)_1ps->scribble);

		if (sp2d->parity == 1)
			_1ps->tx = async_xor(_1ps->pages[sp2d->data_devs],
						_1ps->pages, 0, sp2d->data_devs,
						PAGE_SIZE, &_1ps->submit);
		else /* parity == 2 */
			_1ps->tx = async_gen_syndrome(_1ps->pages, 0,
						sp2d->data_devs + sp2d->parity,
						PAGE_SIZE, &_1ps->submit);
	}

	for (p = 0; p < sp2d->pages_in_unit; p++) {
		struct __1_page_stripe *_1ps = &sp2d->_1p_stripes[p];
		/* NOTE: We wait for HW synchronously (I don't have such HW
		 * to test with.) Is parallelism needed with today's multi
		 * cores?
		 */
		async_tx_issue_pending(_1ps->tx);
	}
}