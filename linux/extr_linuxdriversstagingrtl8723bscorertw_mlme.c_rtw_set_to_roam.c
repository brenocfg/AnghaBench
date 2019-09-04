#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int to_join; scalar_t__ to_roam; } ;
struct adapter {TYPE_1__ mlmepriv; } ;

/* Variables and functions */

inline void rtw_set_to_roam(struct adapter *adapter, u8 to_roam)
{
	if (to_roam == 0)
		adapter->mlmepriv.to_join = false;
	adapter->mlmepriv.to_roam = to_roam;
}