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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  pf; } ;
struct devlink_port_attrs {TYPE_1__ pci_pf; } ;
struct devlink_port {struct devlink_port_attrs attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PCI_PF ; 
 int __devlink_port_attrs_set (struct devlink_port*,int /*<<< orphan*/ ,unsigned char const*,unsigned char) ; 

void devlink_port_attrs_pci_pf_set(struct devlink_port *devlink_port,
				   const unsigned char *switch_id,
				   unsigned char switch_id_len, u16 pf)
{
	struct devlink_port_attrs *attrs = &devlink_port->attrs;
	int ret;

	ret = __devlink_port_attrs_set(devlink_port,
				       DEVLINK_PORT_FLAVOUR_PCI_PF,
				       switch_id, switch_id_len);
	if (ret)
		return;

	attrs->pci_pf.pf = pf;
}