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
typedef  int /*<<< orphan*/  uint32_t ;
struct iscsi_iface_param_info {int param; int /*<<< orphan*/ * value; } ;
struct beiscsi_hba {int /*<<< orphan*/ * ipv6_iface; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_IP_TYPE_V6 ; 
 int EPERM ; 
 int /*<<< orphan*/  ISCSI_IFACE_ENABLE ; 
#define  ISCSI_NET_PARAM_IFACE_ENABLE 129 
#define  ISCSI_NET_PARAM_IPV6_ADDR 128 
 int beiscsi_if_en_static (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int beiscsi_iface_create_ipv6 (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  iscsi_destroy_iface (int /*<<< orphan*/ *) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
beiscsi_iface_config_ipv6(struct Scsi_Host *shost,
			  struct iscsi_iface_param_info *iface_param,
			  void *data, uint32_t dt_len)
{
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	int ret = -EPERM;

	switch (iface_param->param) {
	case ISCSI_NET_PARAM_IFACE_ENABLE:
		if (iface_param->value[0] == ISCSI_IFACE_ENABLE)
			ret = beiscsi_iface_create_ipv6(phba);
		else {
			iscsi_destroy_iface(phba->ipv6_iface);
			phba->ipv6_iface = NULL;
		}
		break;
	case ISCSI_NET_PARAM_IPV6_ADDR:
		ret = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V6,
					   iface_param->value, NULL);
		break;
	}

	return ret;
}