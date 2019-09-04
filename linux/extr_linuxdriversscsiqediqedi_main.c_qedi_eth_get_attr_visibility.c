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
typedef  int umode_t ;

/* Variables and functions */
#define  ISCSI_BOOT_ETH_FLAGS 135 
#define  ISCSI_BOOT_ETH_GATEWAY 134 
#define  ISCSI_BOOT_ETH_INDEX 133 
#define  ISCSI_BOOT_ETH_IP_ADDR 132 
#define  ISCSI_BOOT_ETH_MAC 131 
#define  ISCSI_BOOT_ETH_ORIGIN 130 
#define  ISCSI_BOOT_ETH_SUBNET_MASK 129 
#define  ISCSI_BOOT_ETH_VLAN 128 

__attribute__((used)) static umode_t qedi_eth_get_attr_visibility(void *data, int type)
{
	int rc = 1;

	switch (type) {
	case ISCSI_BOOT_ETH_FLAGS:
	case ISCSI_BOOT_ETH_MAC:
	case ISCSI_BOOT_ETH_INDEX:
	case ISCSI_BOOT_ETH_IP_ADDR:
	case ISCSI_BOOT_ETH_SUBNET_MASK:
	case ISCSI_BOOT_ETH_GATEWAY:
	case ISCSI_BOOT_ETH_ORIGIN:
	case ISCSI_BOOT_ETH_VLAN:
		rc = 0444;
		break;
	default:
		rc = 0;
		break;
	}
	return rc;
}