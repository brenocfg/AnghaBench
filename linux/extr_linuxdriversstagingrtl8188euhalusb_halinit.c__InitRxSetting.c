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
struct adapter {int dummy; } ;

/* Variables and functions */
 int REG_MACID ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int,int) ; 

__attribute__((used)) static void _InitRxSetting(struct adapter *Adapter)
{
	usb_write32(Adapter, REG_MACID, 0x87654321);
	usb_write32(Adapter, 0x0700, 0x87654321);
}