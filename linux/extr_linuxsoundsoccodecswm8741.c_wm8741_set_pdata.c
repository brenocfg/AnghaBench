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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  diff_mode; } ;
struct wm8741_priv {TYPE_1__ pdata; } ;
struct wm8741_platform_data {int dummy; } ;
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 struct wm8741_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct wm8741_platform_data const*,int) ; 
 scalar_t__ of_property_read_u32 (scalar_t__,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wm8741_set_pdata(struct device *dev, struct wm8741_priv *wm8741)
{
	const struct wm8741_platform_data *pdata = dev_get_platdata(dev);
	u32 diff_mode;

	if (dev->of_node) {
		if (of_property_read_u32(dev->of_node, "diff-mode", &diff_mode)
				>= 0)
			wm8741->pdata.diff_mode = diff_mode;
	} else {
		if (pdata != NULL)
			memcpy(&wm8741->pdata, pdata, sizeof(wm8741->pdata));
	}

	return 0;
}