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
 int /*<<< orphan*/  PYB_SLP_SOFT_RESET ; 
 int /*<<< orphan*/  pybsleep_reset_cause ; 

void pyb_sleep_signal_soft_reset (void) {
    pybsleep_reset_cause = PYB_SLP_SOFT_RESET;
}