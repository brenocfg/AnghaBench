#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_5__ {struct v4l2_mbus_framefmt* formats; struct v4l2_subdev subdev; } ;
struct TYPE_4__ {struct v4l2_mbus_framefmt* formats; struct v4l2_subdev subdev; } ;
struct TYPE_6__ {struct v4l2_mbus_framefmt* formats; struct v4l2_subdev subdev; } ;
struct vpfe_resizer_device {TYPE_2__ resizer_b; TYPE_1__ resizer_a; TYPE_3__ crop_resizer; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 int V4L2_SUBDEV_FORMAT_TRY ; 
 struct vpfe_resizer_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,unsigned int) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *
__resizer_get_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		     unsigned int pad, enum v4l2_subdev_format_whence which)
{
	struct vpfe_resizer_device *resizer = v4l2_get_subdevdata(sd);

	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_format(sd, cfg, pad);
	if (&resizer->crop_resizer.subdev == sd)
		return &resizer->crop_resizer.formats[pad];
	if (&resizer->resizer_a.subdev == sd)
		return &resizer->resizer_a.formats[pad];
	if (&resizer->resizer_b.subdev == sd)
		return &resizer->resizer_b.formats[pad];
	return NULL;
}