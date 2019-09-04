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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  oper_channel; } ;
struct adapter {TYPE_1__ mlmeextpriv; } ;

/* Variables and functions */

inline u8 rtw_get_oper_ch(struct adapter *adapter)
{
	return adapter->mlmeextpriv.oper_channel;
}