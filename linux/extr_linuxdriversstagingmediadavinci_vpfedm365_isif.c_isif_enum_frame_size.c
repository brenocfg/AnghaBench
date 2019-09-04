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
struct vpfe_isif_device {int dummy; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {scalar_t__ index; scalar_t__ code; int min_width; int min_height; int max_width; int max_height; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct TYPE_2__ {scalar_t__ code; int width; int height; } ;
struct v4l2_subdev_format {TYPE_1__ format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  isif_try_format (struct vpfe_isif_device*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
isif_enum_frame_size(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		     struct v4l2_subdev_frame_size_enum *fse)
{
	struct vpfe_isif_device *isif = v4l2_get_subdevdata(sd);
	struct v4l2_subdev_format format;

	if (fse->index != 0)
		return -EINVAL;

	format.pad = fse->pad;
	format.format.code = fse->code;
	format.format.width = 1;
	format.format.height = 1;
	format.which = fse->which;
	isif_try_format(isif, cfg, &format);
	fse->min_width = format.format.width;
	fse->min_height = format.format.height;

	if (format.format.code != fse->code)
		return -EINVAL;

	format.pad = fse->pad;
	format.format.code = fse->code;
	format.format.width = -1;
	format.format.height = -1;
	format.which = fse->which;
	isif_try_format(isif, cfg, &format);
	fse->max_width = format.format.width;
	fse->max_height = format.format.height;

	return 0;
}