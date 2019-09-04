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
 int /*<<< orphan*/  rtw_hal_update_ra_mask (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Update_RA_Entry(struct adapter *padapter, u32 mac_id)
{
	rtw_hal_update_ra_mask(padapter, mac_id, 0);
}