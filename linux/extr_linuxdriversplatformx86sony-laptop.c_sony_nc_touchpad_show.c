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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sony_call_snc_handle (int /*<<< orphan*/ ,int,unsigned int*) ; 
 TYPE_1__* tp_ctl ; 

__attribute__((used)) static ssize_t sony_nc_touchpad_show(struct device *dev,
		struct device_attribute *attr, char *buffer)
{
	unsigned int result;

	if (sony_call_snc_handle(tp_ctl->handle, 0x000, &result))
		return -EINVAL;

	return snprintf(buffer, PAGE_SIZE, "%d\n", !(result & 0x01));
}