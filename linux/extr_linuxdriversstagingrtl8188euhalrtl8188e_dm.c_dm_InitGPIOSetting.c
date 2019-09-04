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
struct adapter {int dummy; } ;

/* Variables and functions */
 int GPIOSEL_ENBT ; 
 int GPIOSEL_GPIO ; 
 int /*<<< orphan*/  REG_GPIO_MUXCFG ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_InitGPIOSetting(struct adapter *Adapter)
{
	u8	tmp1byte;

	tmp1byte = usb_read8(Adapter, REG_GPIO_MUXCFG);
	tmp1byte &= (GPIOSEL_GPIO | ~GPIOSEL_ENBT);

	usb_write8(Adapter, REG_GPIO_MUXCFG, tmp1byte);
}