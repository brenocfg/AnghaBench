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
struct TYPE_2__ {int mouse_event; } ;

/* Variables and functions */
 TYPE_1__* I ; 
 int /*<<< orphan*/  r_cons_enable_mouse (int) ; 
 int r_cons_readchar () ; 

__attribute__((used)) static int parseMouseEvent() {
	int ch = r_cons_readchar ();
	/* Skip the x/y coordinates */
#if USE_CLICK
	int x = r_cons_readchar () - 33;
	int y = r_cons_readchar () - 33;
#else
	(void) r_cons_readchar ();
	(void) r_cons_readchar ();
#endif
#if USE_CLICK
	if (ch == 35) {
		/* handle click  */
#define CLICK_DEBUG 1
#if CLICK_DEBUG
		r_cons_gotoxy (0, 0);
		r_cons_printf ("Click at %d %d\n", x, y);
		r_cons_flush ();
#endif
		RCons *cons = r_cons_singleton ();
		if (cons->onclick) {
			cons->onclick (cons->data, x, y);
		}
		r_cons_enable_mouse (false);
		(void)r_cons_readchar ();
		return 0;
	}
#endif
	if (ch != 0x20 && ch >= 64 + 32) {
		/* Grab wheel events only */
		I->mouse_event = 1;
		return "kj"[(ch - (64 + 32))&1];
	}

	// temporary disable the mouse wheel to allow select
	r_cons_enable_mouse (false);
	(void)r_cons_readchar ();
	return 0;
}