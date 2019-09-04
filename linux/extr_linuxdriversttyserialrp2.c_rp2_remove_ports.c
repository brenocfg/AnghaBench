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
struct rp2_card {int initialized_ports; TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  rp2_uart_driver ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rp2_remove_ports(struct rp2_card *card)
{
	int i;

	for (i = 0; i < card->initialized_ports; i++)
		uart_remove_one_port(&rp2_uart_driver, &card->ports[i].port);
	card->initialized_ports = 0;
}