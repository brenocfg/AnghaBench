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
struct vpfe_isif_device {int dummy; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  pad; int /*<<< orphan*/  which; int /*<<< orphan*/  format; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISIF_PAD_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* __isif_get_format (struct vpfe_isif_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int isif_config_format (struct vpfe_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isif_try_format (struct vpfe_isif_device*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ *,int) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_isif_device*) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
isif_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *fmt)
{
	struct vpfe_isif_device *isif = v4l2_get_subdevdata(sd);
	struct vpfe_device *vpfe_dev = to_vpfe_device(isif);
	struct v4l2_mbus_framefmt *format;

	format = __isif_get_format(isif, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	isif_try_format(isif, cfg, fmt);
	memcpy(format, &fmt->format, sizeof(*format));

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	if (fmt->pad == ISIF_PAD_SOURCE)
		return isif_config_format(vpfe_dev, fmt->pad);

	return 0;
}