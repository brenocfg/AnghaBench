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
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
#define  SEL_CTRL_D 134 
#define  SEL_CTRL_U 133 
#define  SEL_HOME 132 
#define  SEL_NEXT 131 
#define  SEL_PGDN 130 
#define  SEL_PGUP 129 
#define  SEL_PREV 128 
 int cur ; 
 int curscroll ; 
 int /*<<< orphan*/  move_cursor (int,int) ; 
 int ndents ; 
 int /*<<< orphan*/  xlines ; 

__attribute__((used)) static void handle_screen_move(enum action sel)
{
	int onscreen;

	switch (sel) {
	case SEL_NEXT:
		if (ndents)
			move_cursor((cur + 1) % ndents, 0);
		break;
	case SEL_PREV:
		if (ndents)
			move_cursor((cur + ndents - 1) % ndents, 0);
		break;
	case SEL_PGDN:
		onscreen = xlines - 4;
		move_cursor(curscroll + (onscreen - 1), 1);
		curscroll += onscreen - 1;
		break;
	case SEL_CTRL_D:
		onscreen = xlines - 4;
		move_cursor(curscroll + (onscreen - 1), 1);
		curscroll += onscreen >> 1;
		break;
	case SEL_PGUP: // fallthrough
		onscreen = xlines - 4;
		move_cursor(curscroll, 1);
		curscroll -= onscreen - 1;
		break;
	case SEL_CTRL_U:
		onscreen = xlines - 4;
		move_cursor(curscroll, 1);
		curscroll -= onscreen >> 1;
		break;
	case SEL_HOME:
		move_cursor(0, 1);
		break;
	default: /* case SEL_END: */
		move_cursor(ndents - 1, 1);
		break;
	}
}