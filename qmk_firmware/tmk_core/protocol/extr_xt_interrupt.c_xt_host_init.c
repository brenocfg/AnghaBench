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
 int /*<<< orphan*/  XT_CLOCK_IN () ; 
 int /*<<< orphan*/  XT_CLOCK_LO () ; 
 int /*<<< orphan*/  XT_DATA_IN () ; 
 int /*<<< orphan*/  XT_DATA_LO () ; 
 int /*<<< orphan*/  XT_INT_INIT () ; 
 int /*<<< orphan*/  XT_INT_OFF () ; 
 int /*<<< orphan*/  XT_INT_ON () ; 
 int /*<<< orphan*/  XT_RESET () ; 
 int /*<<< orphan*/  _delay_ms (int) ; 

void xt_host_init(void) {
    XT_INT_INIT();
    XT_INT_OFF();

    /* hard reset */
#ifdef XT_RESET
    XT_RESET();
#endif

    /* soft reset: pull clock line down for 20ms */
    XT_DATA_LO();
    XT_CLOCK_LO();
    _delay_ms(20);

    /* input mode with pullup */
    XT_CLOCK_IN();
    XT_DATA_IN();

    XT_INT_ON();
}