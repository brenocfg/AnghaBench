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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  (* fBtcSet ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_SET_U1_LPS_VAL ; 
 int /*<<< orphan*/  BTC_SET_U1_RPWM_VAL ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void halbtc8723b1ant_SetLpsRpwm(
	PBTC_COEXIST pBtCoexist, u8 lpsVal, u8 rpwmVal
)
{
	u8 lps = lpsVal;
	u8 rpwm = rpwmVal;

	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_U1_LPS_VAL, &lps);
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_U1_RPWM_VAL, &rpwm);
}