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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct v4l2_mbus_framefmt* __isif_get_format (struct vpfe_isif_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct v4l2_mbus_framefmt*,int) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
isif_get_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *fmt)
{
	struct vpfe_isif_device *vpfe_isif = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __isif_get_format(vpfe_isif, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	memcpy(&fmt->format, format, sizeof(fmt->format));

	return 0;
}