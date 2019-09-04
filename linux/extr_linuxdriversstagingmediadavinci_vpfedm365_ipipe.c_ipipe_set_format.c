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
struct vpfe_ipipe_device {scalar_t__ input; scalar_t__ output; struct v4l2_mbus_framefmt* formats; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {size_t pad; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPIPE_INPUT_CCDC ; 
 scalar_t__ IPIPE_INPUT_MEMORY ; 
 scalar_t__ IPIPE_OUTPUT_RESIZER ; 
 size_t IPIPE_PAD_SINK ; 
 size_t IPIPE_PAD_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_mbus_framefmt* __ipipe_get_format (struct vpfe_ipipe_device*,struct v4l2_subdev_pad_config*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipe_try_format (struct vpfe_ipipe_device*,struct v4l2_subdev_pad_config*,size_t,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct vpfe_ipipe_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
ipipe_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
		     struct v4l2_subdev_format *fmt)
{
	struct vpfe_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __ipipe_get_format(ipipe, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	ipipe_try_format(ipipe, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY)
		return 0;

	if (fmt->pad == IPIPE_PAD_SINK &&
	   (ipipe->input == IPIPE_INPUT_CCDC ||
	    ipipe->input == IPIPE_INPUT_MEMORY))
		ipipe->formats[fmt->pad] = fmt->format;
	else if (fmt->pad == IPIPE_PAD_SOURCE &&
		ipipe->output == IPIPE_OUTPUT_RESIZER)
		ipipe->formats[fmt->pad] = fmt->format;
	else
		return -EINVAL;

	return 0;
}