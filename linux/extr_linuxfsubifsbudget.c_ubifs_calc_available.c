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
struct TYPE_2__ {long long total_used; int idx_lebs; scalar_t__ total_dark; scalar_t__ total_dead; } ;
struct ubifs_info {long long main_bytes; int jhead_cnt; long long leb_size; int dark_wm; TYPE_1__ lst; } ;

/* Variables and functions */

long long ubifs_calc_available(const struct ubifs_info *c, int min_idx_lebs)
{
	int subtract_lebs;
	long long available;

	available = c->main_bytes - c->lst.total_used;

	/*
	 * Now 'available' contains theoretically available flash space
	 * assuming there is no index, so we have to subtract the space which
	 * is reserved for the index.
	 */
	subtract_lebs = min_idx_lebs;

	/* Take into account that GC reserves one LEB for its own needs */
	subtract_lebs += 1;

	/*
	 * The GC journal head LEB is not really accessible. And since
	 * different write types go to different heads, we may count only on
	 * one head's space.
	 */
	subtract_lebs += c->jhead_cnt - 1;

	/* We also reserve one LEB for deletions, which bypass budgeting */
	subtract_lebs += 1;

	available -= (long long)subtract_lebs * c->leb_size;

	/* Subtract the dead space which is not available for use */
	available -= c->lst.total_dead;

	/*
	 * Subtract dark space, which might or might not be usable - it depends
	 * on the data which we have on the media and which will be written. If
	 * this is a lot of uncompressed or not-compressible data, the dark
	 * space cannot be used.
	 */
	available -= c->lst.total_dark;

	/*
	 * However, there is more dark space. The index may be bigger than
	 * @min_idx_lebs. Those extra LEBs are assumed to be available, but
	 * their dark space is not included in total_dark, so it is subtracted
	 * here.
	 */
	if (c->lst.idx_lebs > min_idx_lebs) {
		subtract_lebs = c->lst.idx_lebs - min_idx_lebs;
		available -= subtract_lebs * c->dark_wm;
	}

	/* The calculations are rough and may end up with a negative number */
	return available > 0 ? available : 0;
}