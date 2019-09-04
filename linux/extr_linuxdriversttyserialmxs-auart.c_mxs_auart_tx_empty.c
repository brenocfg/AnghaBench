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
struct mxs_auart_port {int dummy; } ;

/* Variables and functions */
 int AUART_STAT_BUSY ; 
 int AUART_STAT_TXFE ; 
 int /*<<< orphan*/  REG_STAT ; 
 unsigned int TIOCSER_TEMT ; 
 int mxs_read (struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 struct mxs_auart_port* to_auart_port (struct uart_port*) ; 

__attribute__((used)) static unsigned int mxs_auart_tx_empty(struct uart_port *u)
{
	struct mxs_auart_port *s = to_auart_port(u);

	if ((mxs_read(s, REG_STAT) &
		 (AUART_STAT_TXFE | AUART_STAT_BUSY)) == AUART_STAT_TXFE)
		return TIOCSER_TEMT;

	return 0;
}