#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pf; int vf; } ;
struct TYPE_5__ {int pf; } ;
struct TYPE_4__ {int port_number; int split_subport_number; } ;
struct devlink_port_attrs {int flavour; TYPE_3__ pci_vf; TYPE_2__ pci_pf; TYPE_1__ phys; int /*<<< orphan*/  split; int /*<<< orphan*/  set; } ;
struct devlink_port {struct devlink_port_attrs attrs; } ;

/* Variables and functions */
#define  DEVLINK_PORT_FLAVOUR_CPU 132 
#define  DEVLINK_PORT_FLAVOUR_DSA 131 
#define  DEVLINK_PORT_FLAVOUR_PCI_PF 130 
#define  DEVLINK_PORT_FLAVOUR_PCI_VF 129 
#define  DEVLINK_PORT_FLAVOUR_PHYSICAL 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int snprintf (char*,size_t,char*,int,...) ; 

__attribute__((used)) static int __devlink_port_phys_port_name_get(struct devlink_port *devlink_port,
					     char *name, size_t len)
{
	struct devlink_port_attrs *attrs = &devlink_port->attrs;
	int n = 0;

	if (!attrs->set)
		return -EOPNOTSUPP;

	switch (attrs->flavour) {
	case DEVLINK_PORT_FLAVOUR_PHYSICAL:
		if (!attrs->split)
			n = snprintf(name, len, "p%u", attrs->phys.port_number);
		else
			n = snprintf(name, len, "p%us%u",
				     attrs->phys.port_number,
				     attrs->phys.split_subport_number);
		break;
	case DEVLINK_PORT_FLAVOUR_CPU:
	case DEVLINK_PORT_FLAVOUR_DSA:
		/* As CPU and DSA ports do not have a netdevice associated
		 * case should not ever happen.
		 */
		WARN_ON(1);
		return -EINVAL;
	case DEVLINK_PORT_FLAVOUR_PCI_PF:
		n = snprintf(name, len, "pf%u", attrs->pci_pf.pf);
		break;
	case DEVLINK_PORT_FLAVOUR_PCI_VF:
		n = snprintf(name, len, "pf%uvf%u",
			     attrs->pci_vf.pf, attrs->pci_vf.vf);
		break;
	}

	if (n >= len)
		return -EINVAL;

	return 0;
}