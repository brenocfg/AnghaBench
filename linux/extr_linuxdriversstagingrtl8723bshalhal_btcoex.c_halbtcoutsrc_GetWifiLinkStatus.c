#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct adapter {int dummy; } ;
struct TYPE_3__ {struct adapter* Adapter; } ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int _halbtcoutsrc_GetWifiLinkStatus (struct adapter*) ; 

__attribute__((used)) static u32 halbtcoutsrc_GetWifiLinkStatus(PBTC_COEXIST pBtCoexist)
{
	/*  */
	/*  return value: */
	/*  [31:16]=> connected port number */
	/*  [15:0]=> port connected bit define */
	/*  */

	struct adapter *padapter;
	u32 retVal;
	u32 portConnectedStatus, numOfConnectedPort;


	padapter = pBtCoexist->Adapter;
	portConnectedStatus = 0;
	numOfConnectedPort = 0;

	retVal = _halbtcoutsrc_GetWifiLinkStatus(padapter);
	if (retVal) {
		portConnectedStatus |= retVal;
		numOfConnectedPort++;
	}

	retVal = (numOfConnectedPort << 16) | portConnectedStatus;

	return retVal;
}