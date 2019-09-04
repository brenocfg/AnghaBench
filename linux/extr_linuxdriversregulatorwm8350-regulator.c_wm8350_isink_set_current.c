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
 int WM8350_CS1_ISEL_MASK ; 
 int /*<<< orphan*/  WM8350_CURRENT_SINK_DRIVER_A ; 
 int /*<<< orphan*/  WM8350_CURRENT_SINK_DRIVER_B ; 
#define  WM8350_ISINK_A 129 
#define  WM8350_ISINK_B 128 
 int get_isink_val (int,int,int*) ; 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_isink_set_current(struct regulator_dev *rdev, int min_uA,
	int max_uA)
{
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);
	int isink = rdev_get_id(rdev);
	u16 val, setting;
	int ret;

	ret = get_isink_val(min_uA, max_uA, &setting);
	if (ret != 0)
		return ret;

	switch (isink) {
	case WM8350_ISINK_A:
		val = wm8350_reg_read(wm8350, WM8350_CURRENT_SINK_DRIVER_A) &
		    ~WM8350_CS1_ISEL_MASK;
		wm8350_reg_write(wm8350, WM8350_CURRENT_SINK_DRIVER_A,
				 val | setting);
		break;
	case WM8350_ISINK_B:
		val = wm8350_reg_read(wm8350, WM8350_CURRENT_SINK_DRIVER_B) &
		    ~WM8350_CS1_ISEL_MASK;
		wm8350_reg_write(wm8350, WM8350_CURRENT_SINK_DRIVER_B,
				 val | setting);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}