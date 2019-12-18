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
 int /*<<< orphan*/  get_mods () ; 
 int /*<<< orphan*/  get_oneshot_mods () ; 
 int /*<<< orphan*/  set_rgb_indicators (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void matrix_scan_rgb(void) {
  set_rgb_indicators(get_mods(), get_oneshot_mods());
}