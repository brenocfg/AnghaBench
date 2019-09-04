#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  MaxPower; } ;
struct TYPE_4__ {TYPE_1__ c; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ERANGE ; 
 int kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* to_config_usb_cfg (struct config_item*) ; 

__attribute__((used)) static ssize_t gadget_config_desc_MaxPower_store(struct config_item *item,
		const char *page, size_t len)
{
	u16 val;
	int ret;
	ret = kstrtou16(page, 0, &val);
	if (ret)
		return ret;
	if (DIV_ROUND_UP(val, 8) > 0xff)
		return -ERANGE;
	to_config_usb_cfg(item)->c.MaxPower = val;
	return len;
}