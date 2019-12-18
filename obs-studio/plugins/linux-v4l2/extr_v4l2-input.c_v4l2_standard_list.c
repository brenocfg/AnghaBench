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
struct v4l2_standard {int id; scalar_t__ index; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_ENUMSTD ; 
 char* obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_property_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_standard*) ; 

__attribute__((used)) static void v4l2_standard_list(int dev, obs_property_t *prop)
{
	struct v4l2_standard std;
	std.index = 0;

	obs_property_list_clear(prop);

	obs_property_list_add_int(prop, obs_module_text("LeaveUnchanged"), -1);

	while (v4l2_ioctl(dev, VIDIOC_ENUMSTD, &std) == 0) {
		obs_property_list_add_int(prop, (char *)std.name, std.id);
		std.index++;
	}
}