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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct iss_ipipeif_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct v4l2_mbus_framefmt* __ipipeif_get_format (struct iss_ipipeif_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iss_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ipipeif_get_format(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *fmt)
{
	struct iss_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __ipipeif_get_format(ipipeif, cfg, fmt->pad, fmt->which);
	if (!format)
		return -EINVAL;

	fmt->format = *format;
	return 0;
}