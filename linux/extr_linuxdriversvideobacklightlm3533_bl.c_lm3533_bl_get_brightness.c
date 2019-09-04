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
struct lm3533_bl {int /*<<< orphan*/  cb; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 struct lm3533_bl* bl_get_data (struct backlight_device*) ; 
 int lm3533_ctrlbank_get_brightness (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int lm3533_bl_get_brightness(struct backlight_device *bd)
{
	struct lm3533_bl *bl = bl_get_data(bd);
	u8 val;
	int ret;

	ret = lm3533_ctrlbank_get_brightness(&bl->cb, &val);
	if (ret)
		return ret;

	return val;
}