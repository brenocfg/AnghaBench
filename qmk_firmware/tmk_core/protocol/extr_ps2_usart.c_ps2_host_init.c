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
 int /*<<< orphan*/  PS2_USART_INIT () ; 
 int /*<<< orphan*/  PS2_USART_RX_INT_ON () ; 
 int /*<<< orphan*/  idle () ; 

void ps2_host_init(void) {
    idle();  // without this many USART errors occur when cable is disconnected
    PS2_USART_INIT();
    PS2_USART_RX_INT_ON();
    // POR(150-2000ms) plus BAT(300-500ms) may take 2.5sec([3]p.20)
    //_delay_ms(2500);
}