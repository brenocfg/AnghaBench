#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_5__ {TYPE_1__* sc_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sal_wakeup_transmit ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSMIT_BUFFERED ; 
 TYPE_2__ sal_console_port ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snp_start_tx(struct uart_port *port)
{
	if (sal_console_port.sc_ops->sal_wakeup_transmit)
		sal_console_port.sc_ops->sal_wakeup_transmit(&sal_console_port,
							     TRANSMIT_BUFFERED);

}