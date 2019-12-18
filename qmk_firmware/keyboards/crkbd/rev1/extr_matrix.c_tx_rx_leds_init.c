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
 int /*<<< orphan*/  RXLED0 ; 
 int /*<<< orphan*/  TXLED0 ; 
 int /*<<< orphan*/  TX_RX_LED_INIT ; 

void tx_rx_leds_init(void)
{
#ifndef NO_DEBUG_LEDS
    TX_RX_LED_INIT;
    TXLED0;
    RXLED0;
#endif
}