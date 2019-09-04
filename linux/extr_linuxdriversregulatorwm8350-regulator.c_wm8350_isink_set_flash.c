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
typedef  int u16 ;
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8350_CS1_FLASH_MODE ; 
 int WM8350_CS1_TRIGSRC ; 
 int WM8350_CS2_FLASH_MODE ; 
 int WM8350_CS2_TRIGSRC ; 
 int /*<<< orphan*/  WM8350_CSA_FLASH_CONTROL ; 
 int /*<<< orphan*/  WM8350_CSB_FLASH_CONTROL ; 
#define  WM8350_ISINK_A 129 
#define  WM8350_ISINK_B 128 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 

int wm8350_isink_set_flash(struct wm8350 *wm8350, int isink, u16 mode,
			   u16 trigger, u16 duration, u16 on_ramp, u16 off_ramp,
			   u16 drive)
{
	switch (isink) {
	case WM8350_ISINK_A:
		wm8350_reg_write(wm8350, WM8350_CSA_FLASH_CONTROL,
				 (mode ? WM8350_CS1_FLASH_MODE : 0) |
				 (trigger ? WM8350_CS1_TRIGSRC : 0) |
				 duration | on_ramp | off_ramp | drive);
		break;
	case WM8350_ISINK_B:
		wm8350_reg_write(wm8350, WM8350_CSB_FLASH_CONTROL,
				 (mode ? WM8350_CS2_FLASH_MODE : 0) |
				 (trigger ? WM8350_CS2_TRIGSRC : 0) |
				 duration | on_ramp | off_ramp | drive);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}