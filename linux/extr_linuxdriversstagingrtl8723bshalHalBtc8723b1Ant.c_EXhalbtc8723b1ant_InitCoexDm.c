#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bStopCoexDm; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_MSG_INTERFACE ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INTF_INIT ; 
 int /*<<< orphan*/  halbtc8723b1ant_InitCoexDm (TYPE_1__*) ; 
 int /*<<< orphan*/  halbtc8723b1ant_QueryBtInfo (TYPE_1__*) ; 

void EXhalbtc8723b1ant_InitCoexDm(PBTC_COEXIST pBtCoexist)
{
	BTC_PRINT(
		BTC_MSG_INTERFACE,
		INTF_INIT,
		("[BTCoex], Coex Mechanism Init!!\n")
	);

	pBtCoexist->bStopCoexDm = false;

	halbtc8723b1ant_InitCoexDm(pBtCoexist);

	halbtc8723b1ant_QueryBtInfo(pBtCoexist);
}