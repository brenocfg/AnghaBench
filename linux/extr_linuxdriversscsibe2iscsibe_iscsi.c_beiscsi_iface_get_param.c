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
struct iscsi_iface {int /*<<< orphan*/  iface_type; } ;
struct beiscsi_hba {int /*<<< orphan*/  ipv6_iface; int /*<<< orphan*/  ipv4_iface; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {char addr; } ;
struct be_cmd_get_def_gateway_resp {TYPE_1__ ip_addr; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  gateway ;
typedef  enum iscsi_param_type { ____Placeholder_iscsi_param_type } iscsi_param_type ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_IP_TYPE_V4 ; 
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  ISCSI_IFACE_TYPE_IPV4 ; 
 int /*<<< orphan*/  ISCSI_IFACE_TYPE_IPV6 ; 
 int ISCSI_NET_PARAM ; 
#define  ISCSI_NET_PARAM_IFACE_ENABLE 136 
#define  ISCSI_NET_PARAM_IPV4_ADDR 135 
#define  ISCSI_NET_PARAM_IPV4_BOOTPROTO 134 
#define  ISCSI_NET_PARAM_IPV4_GW 133 
#define  ISCSI_NET_PARAM_IPV4_SUBNET 132 
#define  ISCSI_NET_PARAM_IPV6_ADDR 131 
#define  ISCSI_NET_PARAM_VLAN_ENABLED 130 
#define  ISCSI_NET_PARAM_VLAN_ID 129 
#define  ISCSI_NET_PARAM_VLAN_PRIORITY 128 
 int /*<<< orphan*/  KERN_INFO ; 
 int __beiscsi_iface_get_param (struct beiscsi_hba*,struct iscsi_iface*,int,char*) ; 
 int /*<<< orphan*/  beiscsi_hba_is_online (struct beiscsi_hba*) ; 
 int beiscsi_if_get_gw (struct beiscsi_hba*,int /*<<< orphan*/ ,struct be_cmd_get_def_gateway_resp*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* iscsi_iface_to_shost (struct iscsi_iface*) ; 
 int /*<<< orphan*/  memset (struct be_cmd_get_def_gateway_resp*,int /*<<< orphan*/ ,int) ; 
 int sprintf (char*,char*,char*) ; 

int beiscsi_iface_get_param(struct iscsi_iface *iface,
			    enum iscsi_param_type param_type,
			    int param, char *buf)
{
	struct Scsi_Host *shost = iscsi_iface_to_shost(iface);
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	struct be_cmd_get_def_gateway_resp gateway;
	int len = -EPERM;

	if (param_type != ISCSI_NET_PARAM)
		return 0;
	if (!beiscsi_hba_is_online(phba)) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		return -EBUSY;
	}

	switch (param) {
	case ISCSI_NET_PARAM_IPV4_ADDR:
	case ISCSI_NET_PARAM_IPV4_SUBNET:
	case ISCSI_NET_PARAM_IPV4_BOOTPROTO:
	case ISCSI_NET_PARAM_IPV6_ADDR:
	case ISCSI_NET_PARAM_VLAN_ENABLED:
	case ISCSI_NET_PARAM_VLAN_ID:
	case ISCSI_NET_PARAM_VLAN_PRIORITY:
		len = __beiscsi_iface_get_param(phba, iface, param, buf);
		break;
	case ISCSI_NET_PARAM_IFACE_ENABLE:
		if (iface->iface_type == ISCSI_IFACE_TYPE_IPV4)
			len = sprintf(buf, "%s\n",
				      phba->ipv4_iface ? "enable" : "disable");
		else if (iface->iface_type == ISCSI_IFACE_TYPE_IPV6)
			len = sprintf(buf, "%s\n",
				      phba->ipv6_iface ? "enable" : "disable");
		break;
	case ISCSI_NET_PARAM_IPV4_GW:
		memset(&gateway, 0, sizeof(gateway));
		len = beiscsi_if_get_gw(phba, BEISCSI_IP_TYPE_V4, &gateway);
		if (!len)
			len = sprintf(buf, "%pI4\n", &gateway.ip_addr.addr);
		break;
	}

	return len;
}