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
 int /*<<< orphan*/  AUART_CTRL2_TXE ; 
 int /*<<< orphan*/  REG_CTRL2 ; 
 int /*<<< orphan*/  mxs_clr (int /*<<< orphan*/ ,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 struct mxs_auart_port* to_auart_port (struct uart_port*) ; 

__attribute__((used)) static void mxs_auart_stop_tx(struct uart_port *u)
{
	struct mxs_auart_port *s = to_auart_port(u);

	mxs_clr(AUART_CTRL2_TXE, s, REG_CTRL2);
}