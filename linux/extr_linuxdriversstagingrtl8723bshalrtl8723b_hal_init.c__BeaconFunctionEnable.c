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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int DIS_BCNQ_SUB ; 
 int DIS_TSF_UDT ; 
 int EN_BCN_FUNCTION ; 
 scalar_t__ REG_BCN_CTRL ; 
 scalar_t__ REG_RD_CTRL ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static void _BeaconFunctionEnable(struct adapter *padapter, u8 Enable, u8 Linked)
{
	rtw_write8(padapter, REG_BCN_CTRL, DIS_TSF_UDT | EN_BCN_FUNCTION | DIS_BCNQ_SUB);
	rtw_write8(padapter, REG_RD_CTRL+1, 0x6F);
}