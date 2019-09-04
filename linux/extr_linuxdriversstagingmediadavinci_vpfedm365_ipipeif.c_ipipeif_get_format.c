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
struct vpfe_ipipeif_device {int /*<<< orphan*/ * formats; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {scalar_t__ which; size_t pad; int /*<<< orphan*/  format; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct vpfe_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/ * v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,size_t) ; 

__attribute__((used)) static int
ipipeif_get_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *fmt)
{
	struct vpfe_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);

	if (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		fmt->format = ipipeif->formats[fmt->pad];
	else
		fmt->format = *(v4l2_subdev_get_try_format(sd, cfg, fmt->pad));

	return 0;
}