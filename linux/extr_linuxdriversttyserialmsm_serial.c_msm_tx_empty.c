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
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 int /*<<< orphan*/  UART_SR ; 
 int UART_SR_TX_EMPTY ; 
 int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int msm_tx_empty(struct uart_port *port)
{
	return (msm_read(port, UART_SR) & UART_SR_TX_EMPTY) ? TIOCSER_TEMT : 0;
}