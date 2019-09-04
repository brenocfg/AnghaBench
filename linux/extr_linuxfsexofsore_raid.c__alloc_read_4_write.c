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
struct ore_layout {int group_width; int mirrors_p1; } ;
struct ore_io_state {int /*<<< orphan*/  ios_read_4_write; int /*<<< orphan*/  oc; TYPE_1__* sp2d; struct ore_layout* layout; } ;
struct TYPE_2__ {int pages_in_unit; } ;

/* Variables and functions */
 int _ore_get_io_state (struct ore_layout*,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _alloc_read_4_write(struct ore_io_state *ios)
{
	struct ore_layout *layout = ios->layout;
	int ret;
	/* We want to only read those pages not in cache so worst case
	 * is a stripe populated with every other page
	 */
	unsigned sgs_per_dev = ios->sp2d->pages_in_unit + 2;

	ret = _ore_get_io_state(layout, ios->oc,
				layout->group_width * layout->mirrors_p1,
				sgs_per_dev, 0, &ios->ios_read_4_write);
	return ret;
}