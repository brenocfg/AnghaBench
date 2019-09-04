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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
#define  WMI_BEACON_SVC 136 
#define  WMI_CAB_SVC 135 
#define  WMI_CONTROL_SVC 134 
#define  WMI_DATA_BE_SVC 133 
#define  WMI_DATA_BK_SVC 132 
#define  WMI_DATA_VI_SVC 131 
#define  WMI_DATA_VO_SVC 130 
#define  WMI_MGMT_SVC 129 
#define  WMI_UAPSD_SVC 128 

__attribute__((used)) static u8 service_to_dlpipe(u16 service_id)
{
	switch (service_id) {
	case WMI_CONTROL_SVC:
		return 3;
	case WMI_BEACON_SVC:
	case WMI_CAB_SVC:
	case WMI_UAPSD_SVC:
	case WMI_MGMT_SVC:
	case WMI_DATA_VO_SVC:
	case WMI_DATA_VI_SVC:
	case WMI_DATA_BE_SVC:
	case WMI_DATA_BK_SVC:
		return 2;
	default:
		return 0;
	}
}