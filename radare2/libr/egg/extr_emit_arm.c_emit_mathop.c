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
typedef  int /*<<< orphan*/  REgg ;

/* Variables and functions */
 char* R_AX ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,char*,char const*,char const*) ; 

__attribute__((used)) static void emit_mathop(REgg *egg, int ch, int vs, int type, const char *eq, const char *p) {
	char *op;
	switch (ch) {
	case '^': op = "eor"; break;
	case '&': op = "and"; break;
	case '|': op = "orr"; break;
	case '-': op = "sub"; break;
	case '+': op = "add"; break;
	case '*': op = "mul"; break;
	case '/': op = "div"; break;
	default:  op = "mov"; break;
	}
	if (!eq) {
		eq = R_AX;
	}
	if (!p) {
		p = R_AX;
	}
#if 0
	// TODO:
	eprintf ("TYPE = %c\n", type);
	eprintf ("  %s%c %c%s, %s\n", op, vs, type, eq, p);
	eprintf ("  %s %s, [%s]\n", op, p, eq);
#endif
	if (type == '*') {
		r_egg_printf (egg, "  %s %s, [%s]\n", op, p, eq);
	} else {
		r_egg_printf (egg, "  %s %s, %s\n", op, p, eq);
	}
}