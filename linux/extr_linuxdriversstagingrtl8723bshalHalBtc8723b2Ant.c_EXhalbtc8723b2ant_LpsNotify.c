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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int bUnderLps; } ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 scalar_t__ BTC_LPS_DISABLE ; 
 scalar_t__ BTC_LPS_ENABLE ; 
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INTF_NOTIFY ; 
 TYPE_1__* pCoexSta ; 

void EXhalbtc8723b2ant_LpsNotify(PBTC_COEXIST pBtCoexist, u8 type)
{
	if (BTC_LPS_ENABLE == type) {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], LPS ENABLE notify\n"));
		pCoexSta->bUnderLps = true;
	} else if (BTC_LPS_DISABLE == type) {
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], LPS DISABLE notify\n"));
		pCoexSta->bUnderLps = false;
	}
}