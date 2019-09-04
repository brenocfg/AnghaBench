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
struct hal_data_8188e {int ReceiveConfig; } ;
struct adapter {struct hal_data_8188e* HalData; } ;

/* Variables and functions */
 int RCR_AAP ; 
 int RCR_AB ; 
 int RCR_AM ; 
 int RCR_AMF ; 
 int RCR_APM ; 
 int RCR_APP_ICV ; 
 int RCR_APP_MIC ; 
 int RCR_APP_PHYSTS ; 
 int RCR_CBSSID_BCN ; 
 int RCR_CBSSID_DATA ; 
 int RCR_HTC_LOC_CTRL ; 
 scalar_t__ REG_MAR ; 
 scalar_t__ REG_RCR ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void _InitWMACSetting(struct adapter *Adapter)
{
	struct hal_data_8188e *haldata = Adapter->HalData;

	haldata->ReceiveConfig = RCR_AAP | RCR_APM | RCR_AM | RCR_AB |
				  RCR_CBSSID_DATA | RCR_CBSSID_BCN |
				  RCR_APP_ICV | RCR_AMF | RCR_HTC_LOC_CTRL |
				  RCR_APP_MIC | RCR_APP_PHYSTS;

	/*  some REG_RCR will be modified later by phy_ConfigMACWithHeaderFile() */
	usb_write32(Adapter, REG_RCR, haldata->ReceiveConfig);

	/*  Accept all multicast address */
	usb_write32(Adapter, REG_MAR, 0xFFFFFFFF);
	usb_write32(Adapter, REG_MAR + 4, 0xFFFFFFFF);
}