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
struct page {int dummy; } ;
struct ore_io_state {unsigned int cur_par_page; scalar_t__ ios_read_4_write; TYPE_1__* per_dev; scalar_t__ extra_part_alloc; scalar_t__ sp2d; int /*<<< orphan*/  private; int /*<<< orphan*/  r4w; struct page** parity_pages; } ;
struct TYPE_2__ {struct page** sglist; } ;

/* Variables and functions */
 int /*<<< orphan*/  _raid_page_free (struct page*) ; 
 int /*<<< orphan*/  _sp2d_free (scalar_t__) ; 
 int /*<<< orphan*/  _sp2d_reset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  ore_put_io_state (scalar_t__) ; 

void _ore_free_raid_stuff(struct ore_io_state *ios)
{
	if (ios->sp2d) { /* writing and raid */
		unsigned i;

		for (i = 0; i < ios->cur_par_page; i++) {
			struct page *page = ios->parity_pages[i];

			if (page)
				_raid_page_free(page);
		}
		if (ios->extra_part_alloc)
			kfree(ios->parity_pages);
		/* If IO returned an error pages might need unlocking */
		_sp2d_reset(ios->sp2d, ios->r4w, ios->private);
		_sp2d_free(ios->sp2d);
	} else {
		/* Will only be set if raid reading && sglist is big */
		if (ios->extra_part_alloc)
			kfree(ios->per_dev[0].sglist);
	}
	if (ios->ios_read_4_write)
		ore_put_io_state(ios->ios_read_4_write);
}