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
struct ab8500_usb {int /*<<< orphan*/  dev; int /*<<< orphan*/  ab8500; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_USB ; 
 int /*<<< orphan*/  AB8500_USB_PHY_CTRL_REG ; 
 int /*<<< orphan*/  AB8500_V20_31952_DISABLE_DELAY_US ; 
 int /*<<< orphan*/  abx500_mask_and_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ab8500_2p0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_usb_wd_linkstatus(struct ab8500_usb *ab, u8 bit)
{
	/* Workaround for v2.0 bug # 31952 */
	if (is_ab8500_2p0(ab->ab8500)) {
		abx500_mask_and_set_register_interruptible(ab->dev,
				AB8500_USB, AB8500_USB_PHY_CTRL_REG,
				bit, bit);
		udelay(AB8500_V20_31952_DISABLE_DELAY_US);
	}
}