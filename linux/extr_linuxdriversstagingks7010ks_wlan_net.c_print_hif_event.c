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
struct net_device {int dummy; } ;

/* Variables and functions */
#define  HIF_ADH_SET2_CONF 163 
#define  HIF_ADH_SET2_REQ 162 
#define  HIF_ADH_SET_CONF 161 
#define  HIF_ADH_SET_REQ 160 
#define  HIF_AP_SET_CONF 159 
#define  HIF_AP_SET_REQ 158 
#define  HIF_ASSOC_INFO_IND 157 
#define  HIF_CONNECT_IND 156 
#define  HIF_DATA_IND 155 
#define  HIF_DATA_REQ 154 
#define  HIF_INFRA_SET2_CONF 153 
#define  HIF_INFRA_SET2_REQ 152 
#define  HIF_INFRA_SET_CONF 151 
#define  HIF_INFRA_SET_REQ 150 
#define  HIF_MIB_GET_CONF 149 
#define  HIF_MIB_GET_REQ 148 
#define  HIF_MIB_SET_CONF 147 
#define  HIF_MIB_SET_REQ 146 
#define  HIF_MIC_FAILURE_CONF 145 
#define  HIF_MIC_FAILURE_REQ 144 
#define  HIF_PHY_INFO_CONF 143 
#define  HIF_PHY_INFO_IND 142 
#define  HIF_PHY_INFO_REQ 141 
#define  HIF_POWER_MGMT_CONF 140 
#define  HIF_POWER_MGMT_REQ 139 
#define  HIF_PS_ADH_SET_CONF 138 
#define  HIF_PS_ADH_SET_REQ 137 
#define  HIF_SCAN_CONF 136 
#define  HIF_SCAN_IND 135 
#define  HIF_SCAN_REQ 134 
#define  HIF_SLEEP_CONF 133 
#define  HIF_SLEEP_REQ 132 
#define  HIF_START_CONF 131 
#define  HIF_START_REQ 130 
#define  HIF_STOP_CONF 129 
#define  HIF_STOP_REQ 128 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 

__attribute__((used)) static void print_hif_event(struct net_device *dev, int event)
{
	switch (event) {
	case HIF_DATA_REQ:
		netdev_info(dev, "HIF_DATA_REQ\n");
		break;
	case HIF_DATA_IND:
		netdev_info(dev, "HIF_DATA_IND\n");
		break;
	case HIF_MIB_GET_REQ:
		netdev_info(dev, "HIF_MIB_GET_REQ\n");
		break;
	case HIF_MIB_GET_CONF:
		netdev_info(dev, "HIF_MIB_GET_CONF\n");
		break;
	case HIF_MIB_SET_REQ:
		netdev_info(dev, "HIF_MIB_SET_REQ\n");
		break;
	case HIF_MIB_SET_CONF:
		netdev_info(dev, "HIF_MIB_SET_CONF\n");
		break;
	case HIF_POWER_MGMT_REQ:
		netdev_info(dev, "HIF_POWER_MGMT_REQ\n");
		break;
	case HIF_POWER_MGMT_CONF:
		netdev_info(dev, "HIF_POWER_MGMT_CONF\n");
		break;
	case HIF_START_REQ:
		netdev_info(dev, "HIF_START_REQ\n");
		break;
	case HIF_START_CONF:
		netdev_info(dev, "HIF_START_CONF\n");
		break;
	case HIF_CONNECT_IND:
		netdev_info(dev, "HIF_CONNECT_IND\n");
		break;
	case HIF_STOP_REQ:
		netdev_info(dev, "HIF_STOP_REQ\n");
		break;
	case HIF_STOP_CONF:
		netdev_info(dev, "HIF_STOP_CONF\n");
		break;
	case HIF_PS_ADH_SET_REQ:
		netdev_info(dev, "HIF_PS_ADH_SET_REQ\n");
		break;
	case HIF_PS_ADH_SET_CONF:
		netdev_info(dev, "HIF_PS_ADH_SET_CONF\n");
		break;
	case HIF_INFRA_SET_REQ:
		netdev_info(dev, "HIF_INFRA_SET_REQ\n");
		break;
	case HIF_INFRA_SET_CONF:
		netdev_info(dev, "HIF_INFRA_SET_CONF\n");
		break;
	case HIF_ADH_SET_REQ:
		netdev_info(dev, "HIF_ADH_SET_REQ\n");
		break;
	case HIF_ADH_SET_CONF:
		netdev_info(dev, "HIF_ADH_SET_CONF\n");
		break;
	case HIF_AP_SET_REQ:
		netdev_info(dev, "HIF_AP_SET_REQ\n");
		break;
	case HIF_AP_SET_CONF:
		netdev_info(dev, "HIF_AP_SET_CONF\n");
		break;
	case HIF_ASSOC_INFO_IND:
		netdev_info(dev, "HIF_ASSOC_INFO_IND\n");
		break;
	case HIF_MIC_FAILURE_REQ:
		netdev_info(dev, "HIF_MIC_FAILURE_REQ\n");
		break;
	case HIF_MIC_FAILURE_CONF:
		netdev_info(dev, "HIF_MIC_FAILURE_CONF\n");
		break;
	case HIF_SCAN_REQ:
		netdev_info(dev, "HIF_SCAN_REQ\n");
		break;
	case HIF_SCAN_CONF:
		netdev_info(dev, "HIF_SCAN_CONF\n");
		break;
	case HIF_PHY_INFO_REQ:
		netdev_info(dev, "HIF_PHY_INFO_REQ\n");
		break;
	case HIF_PHY_INFO_CONF:
		netdev_info(dev, "HIF_PHY_INFO_CONF\n");
		break;
	case HIF_SLEEP_REQ:
		netdev_info(dev, "HIF_SLEEP_REQ\n");
		break;
	case HIF_SLEEP_CONF:
		netdev_info(dev, "HIF_SLEEP_CONF\n");
		break;
	case HIF_PHY_INFO_IND:
		netdev_info(dev, "HIF_PHY_INFO_IND\n");
		break;
	case HIF_SCAN_IND:
		netdev_info(dev, "HIF_SCAN_IND\n");
		break;
	case HIF_INFRA_SET2_REQ:
		netdev_info(dev, "HIF_INFRA_SET2_REQ\n");
		break;
	case HIF_INFRA_SET2_CONF:
		netdev_info(dev, "HIF_INFRA_SET2_CONF\n");
		break;
	case HIF_ADH_SET2_REQ:
		netdev_info(dev, "HIF_ADH_SET2_REQ\n");
		break;
	case HIF_ADH_SET2_CONF:
		netdev_info(dev, "HIF_ADH_SET2_CONF\n");
	}
}