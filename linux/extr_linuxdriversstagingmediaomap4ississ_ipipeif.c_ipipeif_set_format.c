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
struct v4l2_subdev_format {int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct iss_ipipeif_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPIPEIF_PAD_SINK ; 
 int /*<<< orphan*/  IPIPEIF_PAD_SOURCE_ISIF_SF ; 
 int /*<<< orphan*/  IPIPEIF_PAD_SOURCE_VP ; 
 struct v4l2_mbus_framefmt* __ipipeif_get_format (struct iss_ipipeif_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipeif_try_format (struct iss_ipipeif_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct iss_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ipipeif_set_format(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *fmt)
{
	struct iss_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __ipipeif_get_format(ipipeif, cfg, fmt->pad, fmt->which);
	if (!format)
		return -EINVAL;

	ipipeif_try_format(ipipeif, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	/* Propagate the format from sink to source */
	if (fmt->pad == IPIPEIF_PAD_SINK) {
		format = __ipipeif_get_format(ipipeif, cfg,
					      IPIPEIF_PAD_SOURCE_ISIF_SF,
					      fmt->which);
		*format = fmt->format;
		ipipeif_try_format(ipipeif, cfg, IPIPEIF_PAD_SOURCE_ISIF_SF,
				   format, fmt->which);

		format = __ipipeif_get_format(ipipeif, cfg,
					      IPIPEIF_PAD_SOURCE_VP,
					      fmt->which);
		*format = fmt->format;
		ipipeif_try_format(ipipeif, cfg, IPIPEIF_PAD_SOURCE_VP, format,
				   fmt->which);
	}

	return 0;
}