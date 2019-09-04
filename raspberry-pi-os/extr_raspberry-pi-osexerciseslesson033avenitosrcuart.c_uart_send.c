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
 int /*<<< orphan*/  UART_DR ; 
 int /*<<< orphan*/  UART_FR ; 
 int get32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,char) ; 

void uart_send ( char c )
{
	while(get32(UART_FR)&0x20) {}			// wait if TX is full
	put32(UART_DR,c);						// when TX is empty, send next char
}