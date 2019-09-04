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
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void emit_frame_end(REgg *egg, int sz, int ctx) {
	if (sz > 0) {
		r_egg_printf (egg, "  add sp, fp, %d\n", sz);
	}
	if (ctx > 0) {
		r_egg_printf (egg, "  pop {fp,pc}\n");
	}
}