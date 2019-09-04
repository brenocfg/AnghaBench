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
struct iscsi_iface {scalar_t__ iface_type; } ;
struct beiscsi_hba {int dummy; } ;
struct TYPE_2__ {int addr; int subnet_mask; } ;
struct be_cmd_get_if_info_resp {int vlan_priority; TYPE_1__ ip_addr; int /*<<< orphan*/  dhcp_state; } ;

/* Variables and functions */
 int BEISCSI_IP_TYPE_V4 ; 
 int BEISCSI_IP_TYPE_V6 ; 
 int BEISCSI_VLAN_DISABLE ; 
 int EINVAL ; 
 scalar_t__ ISCSI_IFACE_TYPE_IPV6 ; 
 int ISCSI_MAX_VLAN_ID ; 
 int ISCSI_MAX_VLAN_PRIORITY ; 
#define  ISCSI_NET_PARAM_IPV4_ADDR 134 
#define  ISCSI_NET_PARAM_IPV4_BOOTPROTO 133 
#define  ISCSI_NET_PARAM_IPV4_SUBNET 132 
#define  ISCSI_NET_PARAM_IPV6_ADDR 131 
#define  ISCSI_NET_PARAM_VLAN_ENABLED 130 
#define  ISCSI_NET_PARAM_VLAN_ID 129 
#define  ISCSI_NET_PARAM_VLAN_PRIORITY 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int beiscsi_if_get_info (struct beiscsi_hba*,int,struct be_cmd_get_if_info_resp**) ; 
 int /*<<< orphan*/  kfree (struct be_cmd_get_if_info_resp*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int __beiscsi_iface_get_param(struct beiscsi_hba *phba,
				     struct iscsi_iface *iface,
				     int param, char *buf)
{
	struct be_cmd_get_if_info_resp *if_info;
	int len, ip_type = BEISCSI_IP_TYPE_V4;

	if (iface->iface_type == ISCSI_IFACE_TYPE_IPV6)
		ip_type = BEISCSI_IP_TYPE_V6;

	len = beiscsi_if_get_info(phba, ip_type, &if_info);
	if (len)
		return len;

	switch (param) {
	case ISCSI_NET_PARAM_IPV4_ADDR:
		len = sprintf(buf, "%pI4\n", if_info->ip_addr.addr);
		break;
	case ISCSI_NET_PARAM_IPV6_ADDR:
		len = sprintf(buf, "%pI6\n", if_info->ip_addr.addr);
		break;
	case ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		if (!if_info->dhcp_state)
			len = sprintf(buf, "static\n");
		else
			len = sprintf(buf, "dhcp\n");
		break;
	case ISCSI_NET_PARAM_IPV4_SUBNET:
		len = sprintf(buf, "%pI4\n", if_info->ip_addr.subnet_mask);
		break;
	case ISCSI_NET_PARAM_VLAN_ENABLED:
		len = sprintf(buf, "%s\n",
			      (if_info->vlan_priority == BEISCSI_VLAN_DISABLE) ?
			      "disable" : "enable");
		break;
	case ISCSI_NET_PARAM_VLAN_ID:
		if (if_info->vlan_priority == BEISCSI_VLAN_DISABLE)
			len = -EINVAL;
		else
			len = sprintf(buf, "%d\n",
				      (if_info->vlan_priority &
				       ISCSI_MAX_VLAN_ID));
		break;
	case ISCSI_NET_PARAM_VLAN_PRIORITY:
		if (if_info->vlan_priority == BEISCSI_VLAN_DISABLE)
			len = -EINVAL;
		else
			len = sprintf(buf, "%d\n",
				      ((if_info->vlan_priority >> 13) &
				       ISCSI_MAX_VLAN_PRIORITY));
		break;
	default:
		WARN_ON(1);
	}

	kfree(if_info);
	return len;
}