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
struct ore_io_state {int numdevs; TYPE_1__* layout; int /*<<< orphan*/  r4w; scalar_t__ sp2d; } ;
struct TYPE_2__ {scalar_t__ mirrors_p1; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int _prepare_for_striping (struct ore_io_state*) ; 
 int _write_mirror (struct ore_io_state*,int) ; 
 int ore_io_execute (struct ore_io_state*) ; 
 scalar_t__ unlikely (int) ; 

int ore_write(struct ore_io_state *ios)
{
	int i;
	int ret;

	if (unlikely(ios->sp2d && !ios->r4w)) {
		/* A library is attempting a RAID-write without providing
		 * a pages lock interface.
		 */
		WARN_ON_ONCE(1);
		return -ENOTSUPP;
	}

	ret = _prepare_for_striping(ios);
	if (unlikely(ret))
		return ret;

	for (i = 0; i < ios->numdevs; i += ios->layout->mirrors_p1) {
		ret = _write_mirror(ios, i);
		if (unlikely(ret))
			return ret;
	}

	ret = ore_io_execute(ios);
	return ret;
}