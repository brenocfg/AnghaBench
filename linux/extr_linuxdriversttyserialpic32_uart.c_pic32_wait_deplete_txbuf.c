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
struct pic32_sport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_UART_STA ; 
 int PIC32_UART_STA_TRMT ; 
 int pic32_uart_readl (struct pic32_sport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void pic32_wait_deplete_txbuf(struct pic32_sport *sport)
{
	/* wait for tx empty, otherwise chars will be lost or corrupted */
	while (!(pic32_uart_readl(sport, PIC32_UART_STA) & PIC32_UART_STA_TRMT))
		udelay(1);
}