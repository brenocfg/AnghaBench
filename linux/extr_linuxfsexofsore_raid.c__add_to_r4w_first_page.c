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
struct page {int /*<<< orphan*/  index; } ;
struct ore_striping_info {unsigned int obj_offset; int /*<<< orphan*/  dev; } ;
struct ore_io_state {int /*<<< orphan*/  offset; int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORE_DBGMSG (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  _LLU (unsigned int) ; 
 int _add_to_r4w (struct ore_io_state*,struct ore_striping_info*,struct page*,unsigned int) ; 
 int /*<<< orphan*/  ore_calc_stripe_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ore_striping_info*) ; 

__attribute__((used)) static int _add_to_r4w_first_page(struct ore_io_state *ios, struct page *page)
{
	struct ore_striping_info si;
	unsigned pg_len;

	ore_calc_stripe_info(ios->layout, ios->offset, 0, &si);

	pg_len = si.obj_offset % PAGE_SIZE;
	si.obj_offset -= pg_len;

	ORE_DBGMSG("offset=0x%llx len=0x%x index=0x%lx dev=%x\n",
		   _LLU(si.obj_offset), pg_len, page->index, si.dev);

	return _add_to_r4w(ios, &si, page, pg_len);
}