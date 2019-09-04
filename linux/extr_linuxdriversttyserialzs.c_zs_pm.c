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
struct zs_port {int /*<<< orphan*/ * regs; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  TxENAB ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zs_pm(struct uart_port *uport, unsigned int state,
		  unsigned int oldstate)
{
	struct zs_port *zport = to_zport(uport);

	if (state < 3)
		zport->regs[5] |= TxENAB;
	else
		zport->regs[5] &= ~TxENAB;
	write_zsreg(zport, R5, zport->regs[5]);
}