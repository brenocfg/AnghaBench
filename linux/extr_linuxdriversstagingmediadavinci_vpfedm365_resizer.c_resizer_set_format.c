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
struct TYPE_6__ {struct v4l2_mbus_framefmt* formats; struct v4l2_subdev subdev; } ;
struct TYPE_5__ {struct v4l2_mbus_framefmt* formats; struct v4l2_subdev subdev; } ;
struct TYPE_4__ {scalar_t__ output; scalar_t__ output2; struct v4l2_mbus_framefmt* formats; struct v4l2_subdev subdev; } ;
struct vpfe_resizer_device {TYPE_3__ resizer_b; TYPE_2__ resizer_a; TYPE_1__ crop_resizer; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {size_t pad; scalar_t__ which; struct v4l2_mbus_framefmt format; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RESIZER_A ; 
 scalar_t__ RESIZER_B ; 
 size_t RESIZER_CROP_PAD_SINK ; 
 size_t RESIZER_CROP_PAD_SOURCE ; 
 size_t RESIZER_CROP_PAD_SOURCE2 ; 
 size_t RESIZER_PAD_SINK ; 
 size_t RESIZER_PAD_SOURCE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* __resizer_get_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  resizer_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,size_t,struct v4l2_mbus_framefmt*,scalar_t__) ; 
 struct vpfe_resizer_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_set_format(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *fmt)
{
	struct vpfe_resizer_device *resizer = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __resizer_get_format(sd, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	resizer_try_format(sd, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	if (&resizer->crop_resizer.subdev == sd) {
		if (fmt->pad == RESIZER_CROP_PAD_SINK) {
			resizer->crop_resizer.formats[fmt->pad] = fmt->format;
		} else if (fmt->pad == RESIZER_CROP_PAD_SOURCE &&
				resizer->crop_resizer.output == RESIZER_A) {
			resizer->crop_resizer.formats[fmt->pad] = fmt->format;
			resizer->crop_resizer.
			formats[RESIZER_CROP_PAD_SOURCE2] = fmt->format;
		} else if (fmt->pad == RESIZER_CROP_PAD_SOURCE2 &&
			resizer->crop_resizer.output2 == RESIZER_B) {
			resizer->crop_resizer.formats[fmt->pad] = fmt->format;
			resizer->crop_resizer.
			formats[RESIZER_CROP_PAD_SOURCE] = fmt->format;
		} else {
			return -EINVAL;
		}
	} else if (&resizer->resizer_a.subdev == sd) {
		if (fmt->pad == RESIZER_PAD_SINK)
			resizer->resizer_a.formats[fmt->pad] = fmt->format;
		else if (fmt->pad == RESIZER_PAD_SOURCE)
			resizer->resizer_a.formats[fmt->pad] = fmt->format;
		else
			return -EINVAL;
	} else if (&resizer->resizer_b.subdev == sd) {
		if (fmt->pad == RESIZER_PAD_SINK)
			resizer->resizer_b.formats[fmt->pad] = fmt->format;
		else if (fmt->pad == RESIZER_PAD_SOURCE)
			resizer->resizer_b.formats[fmt->pad] = fmt->format;
		else
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	return 0;
}