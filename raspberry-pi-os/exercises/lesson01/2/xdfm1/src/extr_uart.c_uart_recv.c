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
 int /*<<< orphan*/  UART_DR_REG ; 
 int /*<<< orphan*/  UART_FR_REG ; 
 char get32 (int /*<<< orphan*/ ) ; 

char uart_recv ( void )
{
	// wait if recv buffer is empty (RXFE)
	while(get32(UART_FR_REG) & (1<<4)) {
	}
	return(get32(UART_DR_REG));
}