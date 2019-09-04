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
struct TYPE_3__ {scalar_t__ sy; scalar_t__ h; } ;
typedef  TYPE_1__ RConsCanvas ;

/* Variables and functions */
#define  APEX_DOT 136 
#define  DOT_APEX 135 
#define  DOT_DOT 134 
#define  DOT_NRM 133 
 scalar_t__ G (int,int) ; 
#define  NRM_APEX 132 
#define  NRM_DOT 131 
#define  NRM_NRM 130 
#define  REV_APEX_APEX 129 
#define  REV_APEX_NRM 128 
 char* RUNECODESTR_CORNER_BL ; 
 char* RUNECODESTR_CORNER_BR ; 
 char* RUNECODESTR_CORNER_TL ; 
 char* RUNECODESTR_CORNER_TR ; 
 char* RUNECODESTR_CURVE_CORNER_BL ; 
 char* RUNECODESTR_CURVE_CORNER_BR ; 
 char* RUNECODESTR_CURVE_CORNER_TL ; 
 char* RUNECODESTR_CURVE_CORNER_TR ; 
 int /*<<< orphan*/  W (char const*) ; 
 int /*<<< orphan*/  r_cons_break_pop () ; 
 int /*<<< orphan*/  r_cons_break_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ r_cons_is_breaked () ; 
 scalar_t__ useUtf8 ; 
 int /*<<< orphan*/  useUtf8Curvy ; 
 char* utf8_line_horiz (int) ; 

__attribute__((used)) static void draw_horizontal_line (RConsCanvas *c, int x, int y, int width, int style, int dot_style) {
	const char *l_corner = "?", *r_corner = "?";
	int i;

	if (width < 1) {
		return;
	}
	/* do not render offscreen horizontal lines */
	if (y + c->sy < 0) {
		return;
	}
	if (y + c->sy > c->h) {
		return;
	}

	switch (style) {
	case APEX_DOT:
		if (useUtf8) {
			if (useUtf8Curvy) {
				l_corner = RUNECODESTR_CURVE_CORNER_BL;
				r_corner = RUNECODESTR_CURVE_CORNER_TR;
			} else {
				l_corner = RUNECODESTR_CORNER_BL;
				r_corner = RUNECODESTR_CORNER_TR;
			}
		} else {
			l_corner = "'";
			r_corner = ".";
		}
		break;
	case DOT_APEX:
		if (useUtf8) {
			if (useUtf8Curvy) {
				l_corner = RUNECODESTR_CURVE_CORNER_TL;
				r_corner = RUNECODESTR_CURVE_CORNER_BR;
			} else {
				l_corner = RUNECODESTR_CORNER_TL;
				r_corner = RUNECODESTR_CORNER_BR;
			}
		} else {
			l_corner = ".";
			r_corner = "'";
		}
		break;
	case REV_APEX_APEX:
		if (useUtf8) {
			if (useUtf8Curvy) {
				l_corner = RUNECODESTR_CURVE_CORNER_BL;
				r_corner = RUNECODESTR_CURVE_CORNER_BR;
			} else {
				l_corner = RUNECODESTR_CORNER_BL;
				r_corner = RUNECODESTR_CORNER_BR;
			}
		} else {
			l_corner = "`";
			r_corner = "'";
		}
		break;
	case DOT_DOT:
		if (useUtf8) {
			if (useUtf8Curvy) {
				l_corner = RUNECODESTR_CURVE_CORNER_TL;
				r_corner = RUNECODESTR_CURVE_CORNER_TR;
			} else {
				l_corner = RUNECODESTR_CORNER_TL;
				r_corner = RUNECODESTR_CORNER_TR;
			}
		} else {
			l_corner = r_corner = ".";
		}
		break;
	case NRM_DOT:
		if (useUtf8) {
			l_corner = utf8_line_horiz (dot_style);
			if (useUtf8Curvy) {
				r_corner = RUNECODESTR_CURVE_CORNER_TR;
			} else {
				r_corner = RUNECODESTR_CORNER_TR;
			}
		} else {
			l_corner = "-";
			r_corner = ".";
		}
		break;
	case NRM_APEX:
		if (useUtf8) {
			l_corner = utf8_line_horiz (dot_style);
			if (useUtf8Curvy) {
				r_corner = RUNECODESTR_CURVE_CORNER_BR;
			} else {
				r_corner = RUNECODESTR_CORNER_BR;
			}
		} else {
			l_corner = "-";
			r_corner = "'";
		}
		break;
	case DOT_NRM:
		if (useUtf8) {
			if (useUtf8Curvy) {
				l_corner = RUNECODESTR_CURVE_CORNER_TL;
			} else {
				l_corner = RUNECODESTR_CORNER_TL;
			}
			r_corner = utf8_line_horiz (dot_style);
		} else {
			l_corner = ".";
			r_corner = "-";
		}
		break;
	case REV_APEX_NRM:
		if (useUtf8) {
			if (useUtf8Curvy) {
				l_corner = RUNECODESTR_CURVE_CORNER_BL;
			} else {
				l_corner = RUNECODESTR_CORNER_BL;
			}
			r_corner = utf8_line_horiz (dot_style);
		} else {
			l_corner = "`";
			r_corner = "-";
		}
		break;
	case NRM_NRM:
	default:
		if (useUtf8) {
			l_corner = r_corner = utf8_line_horiz (dot_style);
		} else {
			l_corner = r_corner = "-";
		}
		break;
	}

	if (G (x, y)) {
		W (l_corner);
	}

	const char *hline = useUtf8 ? utf8_line_horiz (dot_style) : "-";
	r_cons_break_push (NULL, NULL);
	for (i = x + 1; i < x + width - 1; i++) {
		if (r_cons_is_breaked ()) {
			break;
		}
		if (G (i, y)) {
			W (hline);
		}
	}
	r_cons_break_pop ();

	if (G (x + width - 1, y)) {
		W (r_corner);
	}
}