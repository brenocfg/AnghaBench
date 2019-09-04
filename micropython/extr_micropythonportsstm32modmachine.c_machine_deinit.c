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
 int /*<<< orphan*/  PYB_RESET_SOFT ; 
 int /*<<< orphan*/  reset_cause ; 

void machine_deinit(void) {
    // we are doing a soft-reset so change the reset_cause
    reset_cause = PYB_RESET_SOFT;
}