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
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,char const*,char const*,int) ; 

__attribute__((used)) static void emit_set_string(REgg *egg, const char *dstvar, const char *str, int j) {
	// what is j?
	r_egg_printf (egg, "set (\"%s\", \"%s\", %d)\n", dstvar, str, j);
}