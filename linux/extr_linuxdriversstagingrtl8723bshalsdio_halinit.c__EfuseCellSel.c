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
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EFUSE_SEL (int /*<<< orphan*/ ) ; 
 int EFUSE_SEL_MASK ; 
 int /*<<< orphan*/  EFUSE_TEST ; 
 int /*<<< orphan*/  EFUSE_WIFI_SEL_0 ; 
 int rtw_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _EfuseCellSel(struct adapter *padapter)
{
	u32 value32;

	value32 = rtw_read32(padapter, EFUSE_TEST);
	value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_WIFI_SEL_0);
	rtw_write32(padapter, EFUSE_TEST, value32);
}