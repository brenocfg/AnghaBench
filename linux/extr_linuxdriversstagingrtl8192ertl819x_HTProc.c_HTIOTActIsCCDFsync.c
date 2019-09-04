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
struct rtllib_device {TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ IOTPeer; } ;

/* Variables and functions */
 scalar_t__ HT_IOT_PEER_BROADCOM ; 

__attribute__((used)) static u8 HTIOTActIsCCDFsync(struct rtllib_device *ieee)
{
	u8	retValue = 0;

	if (ieee->pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM)
		retValue = 1;
	return retValue;
}