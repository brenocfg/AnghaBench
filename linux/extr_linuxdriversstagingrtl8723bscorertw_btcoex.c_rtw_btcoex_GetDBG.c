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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hal_btcoex_GetDBG (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u32 rtw_btcoex_GetDBG(struct adapter *padapter, u8 *pStrBuf, u32 bufSize)
{
	return hal_btcoex_GetDBG(padapter, pStrBuf, bufSize);
}