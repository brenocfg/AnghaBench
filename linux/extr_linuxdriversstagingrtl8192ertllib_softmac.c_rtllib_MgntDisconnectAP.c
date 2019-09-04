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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct rtllib_device {int /*<<< orphan*/  state; TYPE_1__ current_network; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* SetHwRegHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_CECHK_BSSID ; 
 int /*<<< orphan*/  RTLLIB_NOLINK ; 
 int /*<<< orphan*/  rtllib_MlmeDisassociateRequest (struct rtllib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtllib_MgntDisconnectAP(
	struct rtllib_device *rtllib,
	u8 asRsn
)
{
	bool bFilterOutNonAssociatedBSSID = false;

	bFilterOutNonAssociatedBSSID = false;
	rtllib->SetHwRegHandler(rtllib->dev, HW_VAR_CECHK_BSSID,
				(u8 *)(&bFilterOutNonAssociatedBSSID));
	rtllib_MlmeDisassociateRequest(rtllib, rtllib->current_network.bssid,
				       asRsn);

	rtllib->state = RTLLIB_NOLINK;
}