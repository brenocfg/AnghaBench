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
struct bss_ht {int bdSupportHT; int bdRT2RTAggregation; int bdRT2RTLongSlotTime; int RT2RT_HT_Mode; int /*<<< orphan*/  bdHTSpecVer; scalar_t__ bdHTInfoLen; int /*<<< orphan*/  bdHTInfoBuf; scalar_t__ bdHTCapLen; int /*<<< orphan*/  bdHTCapBuf; } ;
typedef  enum rt_ht_capability { ____Placeholder_rt_ht_capability } rt_ht_capability ;

/* Variables and functions */
 int /*<<< orphan*/  HT_SPEC_VER_IEEE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void HTInitializeBssDesc(struct bss_ht *pBssHT)
{

	pBssHT->bdSupportHT = false;
	memset(pBssHT->bdHTCapBuf, 0, sizeof(pBssHT->bdHTCapBuf));
	pBssHT->bdHTCapLen = 0;
	memset(pBssHT->bdHTInfoBuf, 0, sizeof(pBssHT->bdHTInfoBuf));
	pBssHT->bdHTInfoLen = 0;

	pBssHT->bdHTSpecVer = HT_SPEC_VER_IEEE;

	pBssHT->bdRT2RTAggregation = false;
	pBssHT->bdRT2RTLongSlotTime = false;
	pBssHT->RT2RT_HT_Mode = (enum rt_ht_capability)0;
}