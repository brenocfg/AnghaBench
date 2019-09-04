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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PRIMARY_ADAPTER (struct adapter*) ; 
 scalar_t__ REG_MACID ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void hw_var_set_macaddr(struct adapter *padapter, u8 variable, u8 *val)
{
	u8 idx = 0;
	u32 reg_macid;

	reg_macid = REG_MACID;

	for (idx = 0 ; idx < 6; idx++)
		rtw_write8(GET_PRIMARY_ADAPTER(padapter), (reg_macid+idx), val[idx]);
}