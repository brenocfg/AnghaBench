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

/* Variables and functions */

__attribute__((used)) static void printerr(int error, const char *fmt, ...) {
#if 0
	va_list l;
	va_start (l, fmt);
	if ((sp < 0) || (stack[sp].name == 0)) {
		fprintf (stderr, "internal assembler error, sp == %i\n", sp);
		vfprintf (stderr, fmt, l);
	}
	fprintf (stderr, "%s%s:%d: %s: ", stack[sp].dir? stack[sp].dir->name: "",
		stack[sp].name, stack[sp].line, error? "error": "warning");
	vfprintf (stderr, fmt, l);
	va_end (l);
	if (error) {
		errors++;
	}
#endif
}