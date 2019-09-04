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
struct aty128fb_par {scalar_t__ blitter_may_be_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_STAT ; 
 int /*<<< orphan*/  aty128_flush_pixel_cache (struct aty128fb_par*) ; 
 int /*<<< orphan*/  aty128_reset_engine (struct aty128fb_par*) ; 
 int aty_ld_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_wait_for_fifo (int,struct aty128fb_par*) ; 

__attribute__((used)) static void wait_for_idle(struct aty128fb_par *par)
{
	int i;

	do_wait_for_fifo(64, par);

	for (;;) {
		for (i = 0; i < 2000000; i++) {
			if (!(aty_ld_le32(GUI_STAT) & (1 << 31))) {
				aty128_flush_pixel_cache(par);
				par->blitter_may_be_busy = 0;
				return;
			}
		}
		aty128_reset_engine(par);
	}
}