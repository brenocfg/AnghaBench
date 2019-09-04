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
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,char*,char const*,char const*) ; 

__attribute__((used)) static void emit_get_while_end (REgg *egg, char *str, const char *ctxpush, const char *label) {
	r_egg_printf (egg, "get_while_end (%s, %s, %s)\n", str, ctxpush, label);
}