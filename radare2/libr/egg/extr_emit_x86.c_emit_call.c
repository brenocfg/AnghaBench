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
 scalar_t__ attsyntax ; 
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void emit_call(REgg *egg, const char *str, int atr) {
	if (atr) {
		if (attsyntax) {
			r_egg_printf (egg, "  call *%s\n", str);
		} else {
			r_egg_printf (egg, "  call [%s]\n", str);
		}
	} else {
		r_egg_printf (egg, "  call %s\n", str);
	}
}