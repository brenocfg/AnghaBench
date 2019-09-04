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
 int /*<<< orphan*/  free (char*) ; 
 char* r_egg_mkvar (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,...) ; 
 char* r_str_escape (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void emit_set_string(REgg *egg, const char *dstvar, const char *str, int j) {
	int rest, off = 0;
	off = strlen (str) + 1;
	rest = (off % 4);
	if (rest) {
		rest = 4 - rest;
	}
	off += rest - 4;
	r_egg_printf (egg, "  add pc, %d\n", (off));
	// XXX: does not handle \n and so on.. must use r_util
	// use r_str_escape to handle \n
	// do not forget mem leak
	r_egg_printf (egg, ".string \"%s\"\n", str = r_str_escape (str));
	free ((char *) str);
	if (rest) {
		r_egg_printf (egg, ".fill %d, 1, 0\n", (rest));
	}
	r_egg_printf (egg, "  sub r0, pc, %d\n", off + 12);
	{
		char str[32], *p = r_egg_mkvar (egg, str, dstvar, 0);
		// r_egg_printf (egg, "DSTVAR=%s --> %s\n", dstvar, p);
		r_egg_printf (egg, "  str r0, [%s]\n", p);
		free (p);
	}
}