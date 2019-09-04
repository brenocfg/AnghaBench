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
 int /*<<< orphan*/  lin2_ring ; 
 int /*<<< orphan*/  uart_ring_process (int /*<<< orphan*/ *) ; 

void USART3_IRQHandler(void) { uart_ring_process(&lin2_ring); }