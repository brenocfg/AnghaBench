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
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  split_subport_number; int /*<<< orphan*/  port_number; } ;
struct TYPE_5__ {int pf; int vf; } ;
struct TYPE_4__ {int pf; } ;
struct devlink_port_attrs {int flavour; TYPE_3__ phys; int /*<<< orphan*/  split; TYPE_2__ pci_vf; TYPE_1__ pci_pf; int /*<<< orphan*/  set; } ;
struct devlink_port {struct devlink_port_attrs attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_FLAVOUR ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_NUMBER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_PCI_PF_NUMBER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_PCI_VF_NUMBER ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_SPLIT_GROUP ; 
 int /*<<< orphan*/  DEVLINK_ATTR_PORT_SPLIT_SUBPORT_NUMBER ; 
#define  DEVLINK_PORT_FLAVOUR_CPU 132 
#define  DEVLINK_PORT_FLAVOUR_DSA 131 
#define  DEVLINK_PORT_FLAVOUR_PCI_PF 130 
#define  DEVLINK_PORT_FLAVOUR_PCI_VF 129 
#define  DEVLINK_PORT_FLAVOUR_PHYSICAL 128 
 int EMSGSIZE ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_port_attrs_put(struct sk_buff *msg,
				     struct devlink_port *devlink_port)
{
	struct devlink_port_attrs *attrs = &devlink_port->attrs;

	if (!attrs->set)
		return 0;
	if (nla_put_u16(msg, DEVLINK_ATTR_PORT_FLAVOUR, attrs->flavour))
		return -EMSGSIZE;
	switch (devlink_port->attrs.flavour) {
	case DEVLINK_PORT_FLAVOUR_PCI_PF:
		if (nla_put_u16(msg, DEVLINK_ATTR_PORT_PCI_PF_NUMBER,
				attrs->pci_pf.pf))
			return -EMSGSIZE;
		break;
	case DEVLINK_PORT_FLAVOUR_PCI_VF:
		if (nla_put_u16(msg, DEVLINK_ATTR_PORT_PCI_PF_NUMBER,
				attrs->pci_vf.pf) ||
		    nla_put_u16(msg, DEVLINK_ATTR_PORT_PCI_VF_NUMBER,
				attrs->pci_vf.vf))
			return -EMSGSIZE;
		break;
	case DEVLINK_PORT_FLAVOUR_PHYSICAL:
	case DEVLINK_PORT_FLAVOUR_CPU:
	case DEVLINK_PORT_FLAVOUR_DSA:
		if (nla_put_u32(msg, DEVLINK_ATTR_PORT_NUMBER,
				attrs->phys.port_number))
			return -EMSGSIZE;
		if (!attrs->split)
			return 0;
		if (nla_put_u32(msg, DEVLINK_ATTR_PORT_SPLIT_GROUP,
				attrs->phys.port_number))
			return -EMSGSIZE;
		if (nla_put_u32(msg, DEVLINK_ATTR_PORT_SPLIT_SUBPORT_NUMBER,
				attrs->phys.split_subport_number))
			return -EMSGSIZE;
		break;
	default:
		break;
	}
	return 0;
}