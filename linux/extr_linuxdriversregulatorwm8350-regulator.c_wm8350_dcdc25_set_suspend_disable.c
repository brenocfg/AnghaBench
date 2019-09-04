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
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WM8350_DC2_HIB_MODE_DISABLE ; 
 int WM8350_DC2_HIB_MODE_MASK ; 
 int WM8350_DC2_HIB_MODE_SHIFT ; 
 int WM8350_DC5_HIB_MODE_DISABLE ; 
 int WM8350_DC5_HIB_MODE_MASK ; 
 int WM8350_DC5_HIB_MODE_SHIFT ; 
 int /*<<< orphan*/  WM8350_DCDC2_CONTROL ; 
 int /*<<< orphan*/  WM8350_DCDC5_CONTROL ; 
#define  WM8350_DCDC_2 129 
#define  WM8350_DCDC_5 128 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_dcdc25_set_suspend_disable(struct regulator_dev *rdev)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int dcdc = rdev_get_id(rdev);
	u16 val;

	switch (dcdc) {
	case WM8350_DCDC_2:
		val = wm8350_reg_read(wm8350, WM8350_DCDC2_CONTROL)
		    & ~WM8350_DC2_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC2_CONTROL, val |
		    (WM8350_DC2_HIB_MODE_DISABLE << WM8350_DC2_HIB_MODE_SHIFT));
		break;
	case WM8350_DCDC_5:
		val = wm8350_reg_read(wm8350, WM8350_DCDC5_CONTROL)
		    & ~WM8350_DC5_HIB_MODE_MASK;
		wm8350_reg_write(wm8350, WM8350_DCDC5_CONTROL, val |
		    (WM8350_DC5_HIB_MODE_DISABLE << WM8350_DC5_HIB_MODE_SHIFT));
		break;
	default:
		return -EINVAL;
	}
	return 0;
}