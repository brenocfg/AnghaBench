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
struct ore_layout {unsigned int stripe_unit; int /*<<< orphan*/  parity; int /*<<< orphan*/  group_width; } ;
struct ore_io_state {int /*<<< orphan*/  sp2d; struct ore_layout* layout; scalar_t__ parity_pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ _sp2d_alloc (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int _ore_post_alloc_raid_stuff(struct ore_io_state *ios)
{
	if (ios->parity_pages) {
		struct ore_layout *layout = ios->layout;
		unsigned pages_in_unit = layout->stripe_unit / PAGE_SIZE;

		if (_sp2d_alloc(pages_in_unit, layout->group_width,
				layout->parity, &ios->sp2d)) {
			return -ENOMEM;
		}
	}
	return 0;
}