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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  c2h_evt_read_88xx (struct adapter*,int /*<<< orphan*/ *) ; 

s32 rtw_hal_c2h_evt_read(struct adapter *adapter, u8 *buf)
{
	return c2h_evt_read_88xx(adapter, buf);
}