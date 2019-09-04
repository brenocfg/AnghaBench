#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sx; scalar_t__ w; } ;
typedef  TYPE_1__ RConsCanvas ;

/* Variables and functions */
 scalar_t__ G (int,int) ; 
 int /*<<< orphan*/  W (char const*) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_cons_is_breaked () ; 
 scalar_t__ useUtf8 ; 
 char* utf8_line_vert (int) ; 

__attribute__((used)) static void draw_vertical_line (RConsCanvas *c, int x, int y, int height, int dot_style) {
	int i;
	/* do not render offscreen vertical lines */
	if (x + c->sx < 0) {
		return;
	}
	if (x + c->sx > c->w) {
		return;
	}
	const char *vline = useUtf8 ? utf8_line_vert (dot_style) : "|";
	r_cons_break_push (NULL, NULL);
	for (i = y; i < y + height; i++) {
		if (r_cons_is_breaked ()) {
			break;
		}
		if (G (x, i)) {
			W (vline);
		}
	}
	r_cons_break_pop ();
}