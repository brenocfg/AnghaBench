#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpc52xx_psc_ipcr; } ;

/* Variables and functions */
 TYPE_1__* PSC (struct uart_port*) ; 
 int /*<<< orphan*/  in_8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 mpc52xx_psc_get_ipcr(struct uart_port *port)
{
	return in_8(&PSC(port)->mpc52xx_psc_ipcr);
}