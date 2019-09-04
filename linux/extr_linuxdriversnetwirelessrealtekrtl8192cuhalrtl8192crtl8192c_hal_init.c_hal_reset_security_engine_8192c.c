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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int rtw_read8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_usleep_os (int) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ *,int,int) ; 

void hal_reset_security_engine_8192c(_adapter * adapter)
{
	rtw_write8(adapter, 0x522, 0xFF);
	rtw_write8(adapter, 0x21, 0x35);
	rtw_usleep_os(300);
	rtw_write8(adapter, 0x101, rtw_read8(adapter,0x101)&~0x02);
	rtw_write8(adapter, 0x101, rtw_read8(adapter,0x101)|0x02);
	rtw_write8(adapter, 0x21, 0x55);
	rtw_write8(adapter, 0x522, 0x00);
}