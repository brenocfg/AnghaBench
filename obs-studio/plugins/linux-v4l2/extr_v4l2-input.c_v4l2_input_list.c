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
struct v4l2_input {int /*<<< orphan*/  index; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  int_fast32_t ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  VIDIOC_ENUMINPUT ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_input*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_input*) ; 

__attribute__((used)) static void v4l2_input_list(int_fast32_t dev, obs_property_t *prop)
{
	struct v4l2_input in;
	memset(&in, 0, sizeof(in));

	obs_property_list_clear(prop);

	while (v4l2_ioctl(dev, VIDIOC_ENUMINPUT, &in) == 0) {
		obs_property_list_add_int(prop, (char *)in.name, in.index);
		blog(LOG_INFO, "Found input '%s' (Index %d)", in.name,
		     in.index);
		in.index++;
	}
}