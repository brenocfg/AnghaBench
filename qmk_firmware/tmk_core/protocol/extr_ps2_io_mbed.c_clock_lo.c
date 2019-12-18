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
 int /*<<< orphan*/  PIN_OUTPUT ; 
 int /*<<< orphan*/  clock ; 
 int /*<<< orphan*/  gpio_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void clock_lo(void) {
    gpio_dir(&clock, PIN_OUTPUT);
    gpio_write(&clock, 0);
}