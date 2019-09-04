#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int btdmAntNum; } ;
struct TYPE_8__ {TYPE_1__ boardInfo; } ;
typedef  TYPE_2__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  EXhalbtc8723b1ant_PnpNotify (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXhalbtc8723b2ant_PnpNotify (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtcoutsrc_IsBtCoexistAvailable (TYPE_2__*) ; 

void EXhalbtcoutsrc_PnpNotify(PBTC_COEXIST pBtCoexist, u8 pnpState)
{
	if (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		return;

	/*  */
	/*  currently only 1ant we have to do the notification, */
	/*  once pnp is notified to sleep state, we have to leave LPS that we can sleep normally. */
	/*  */

	if (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_PnpNotify(pBtCoexist, pnpState);
	else if (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_PnpNotify(pBtCoexist, pnpState);
}