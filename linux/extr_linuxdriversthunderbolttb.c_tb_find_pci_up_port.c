#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_port_number; } ;
struct tb_switch {struct tb_port* ports; TYPE_1__ config; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct tb_port {TYPE_2__ config; } ;

/* Variables and functions */
 scalar_t__ TB_TYPE_PCIE_UP ; 

__attribute__((used)) static struct tb_port *tb_find_pci_up_port(struct tb_switch *sw)
{
	int i;
	for (i = 1; i <= sw->config.max_port_number; i++)
		if (sw->ports[i].config.type == TB_TYPE_PCIE_UP)
			return &sw->ports[i];
	return NULL;
}