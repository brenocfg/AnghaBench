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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_DEF_ODM_DBG_LEVEL ; 
 int /*<<< orphan*/  rtw_hal_set_def_var (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline void rtw_odm_dbg_level_set(struct adapter *adapter, u32 level)
{
	rtw_hal_set_def_var(adapter, HW_DEF_ODM_DBG_LEVEL, &level);
}