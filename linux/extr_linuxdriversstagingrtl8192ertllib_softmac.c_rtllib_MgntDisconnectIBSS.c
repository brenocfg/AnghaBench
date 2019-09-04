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
typedef  int u8 ;
struct TYPE_2__ {int* bssid; } ;
struct rtllib_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* SetHwRegHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;TYPE_1__ current_network; void* OpMode; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_CECHK_BSSID ; 
 int /*<<< orphan*/  HW_VAR_MEDIA_STATUS ; 
 int /*<<< orphan*/  RTLLIB_NOLINK ; 
 void* RT_OP_MODE_NO_LINK ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_stop_send_beacons (struct rtllib_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void rtllib_MgntDisconnectIBSS(struct rtllib_device *rtllib)
{
	u8	OpMode;
	u8	i;
	bool	bFilterOutNonAssociatedBSSID = false;

	rtllib->state = RTLLIB_NOLINK;

	for (i = 0; i < 6; i++)
		rtllib->current_network.bssid[i] = 0x55;

	rtllib->OpMode = RT_OP_MODE_NO_LINK;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_BSSID,
				rtllib->current_network.bssid);
	OpMode = RT_OP_MODE_NO_LINK;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_MEDIA_STATUS, &OpMode);
	rtllib_stop_send_beacons(rtllib);

	bFilterOutNonAssociatedBSSID = false;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_CECHK_BSSID,
				(u8 *)(&bFilterOutNonAssociatedBSSID));
	notify_wx_assoc_event(rtllib);

}