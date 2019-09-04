#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct page {int dummy; } ;
struct ore_striping_info {unsigned int cur_pg; unsigned int cur_comp; unsigned int unit_off; int /*<<< orphan*/  par_dev; int /*<<< orphan*/  dev; } ;
struct ore_io_state {TYPE_2__* sp2d; int /*<<< orphan*/  layout; } ;
struct TYPE_4__ {TYPE_1__* _1p_stripes; } ;
struct TYPE_3__ {struct page** pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ORE_DBGMSG (char*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  _LLU (unsigned int) ; 
 int _add_to_r4w (struct ore_io_state*,struct ore_striping_info*,struct page*,unsigned int) ; 
 int /*<<< orphan*/  ore_calc_stripe_info (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct ore_striping_info*) ; 

__attribute__((used)) static int _add_to_r4w_last_page(struct ore_io_state *ios, u64 *offset)
{
	struct ore_striping_info si;
	struct page *page;
	unsigned pg_len, p, c;

	ore_calc_stripe_info(ios->layout, *offset, 0, &si);

	p = si.cur_pg;
	c = si.cur_comp;
	page = ios->sp2d->_1p_stripes[p].pages[c];

	pg_len = PAGE_SIZE - (si.unit_off % PAGE_SIZE);
	*offset += pg_len;

	ORE_DBGMSG("p=%d, c=%d next-offset=0x%llx len=0x%x dev=%x par_dev=%d\n",
		   p, c, _LLU(*offset), pg_len, si.dev, si.par_dev);

	BUG_ON(!page);

	return _add_to_r4w(ios, &si, page, pg_len);
}