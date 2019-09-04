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
struct uart_amba_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void pl011_dma_rx_irq(struct uart_amba_port *uap)
{
}