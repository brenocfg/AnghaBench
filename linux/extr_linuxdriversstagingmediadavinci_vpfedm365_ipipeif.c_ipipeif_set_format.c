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
struct vpfe_ipipeif_device {scalar_t__ input; scalar_t__ output; struct v4l2_mbus_framefmt* formats; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {size_t pad; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPIPEIF_INPUT_NONE ; 
 scalar_t__ IPIPEIF_OUTPUT_NONE ; 
 size_t IPIPEIF_PAD_SINK ; 
 size_t IPIPEIF_PAD_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* __ipipeif_get_format (struct vpfe_ipipeif_device*,struct v4l2_subdev_pad_config*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipeif_try_format (struct vpfe_ipipeif_device*,struct v4l2_subdev_pad_config*,size_t,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct vpfe_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
ipipeif_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *fmt)
{
	struct vpfe_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __ipipeif_get_format(ipipeif, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	ipipeif_try_format(ipipeif, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	if (fmt->pad == IPIPEIF_PAD_SINK &&
	    ipipeif->input != IPIPEIF_INPUT_NONE)
		ipipeif->formats[fmt->pad] = fmt->format;
	else if (fmt->pad == IPIPEIF_PAD_SOURCE &&
		 ipipeif->output != IPIPEIF_OUTPUT_NONE)
		ipipeif->formats[fmt->pad] = fmt->format;
	else
		return -EINVAL;

	return 0;
}