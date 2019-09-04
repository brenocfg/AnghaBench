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
struct vpfe_ipipeif_device {int dummy; } ;
struct TYPE_2__ {void* height; void* width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {TYPE_1__ format; void* which; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 int /*<<< orphan*/  IPIPEIF_PAD_SINK ; 
 int /*<<< orphan*/  IPIPEIF_PAD_SOURCE ; 
 void* IPIPE_MAX_OUTPUT_HEIGHT_A ; 
 void* IPIPE_MAX_OUTPUT_WIDTH_A ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 void* V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  ipipeif_set_default_config (struct vpfe_ipipeif_device*) ; 
 int /*<<< orphan*/  ipipeif_set_format (struct v4l2_subdev*,int /*<<< orphan*/ ,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_format*,int /*<<< orphan*/ ,int) ; 
 struct vpfe_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
ipipeif_init_formats(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
	struct vpfe_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct v4l2_subdev_format format;

	memset(&format, 0, sizeof(format));
	format.pad = IPIPEIF_PAD_SINK;
	format.which = V4L2_SUBDEV_FORMAT_TRY;
	format.format.code = MEDIA_BUS_FMT_SGRBG12_1X12;
	format.format.width = IPIPE_MAX_OUTPUT_WIDTH_A;
	format.format.height = IPIPE_MAX_OUTPUT_HEIGHT_A;
	ipipeif_set_format(sd, fh->pad, &format);

	memset(&format, 0, sizeof(format));
	format.pad = IPIPEIF_PAD_SOURCE;
	format.which = V4L2_SUBDEV_FORMAT_TRY;
	format.format.code = MEDIA_BUS_FMT_UYVY8_2X8;
	format.format.width = IPIPE_MAX_OUTPUT_WIDTH_A;
	format.format.height = IPIPE_MAX_OUTPUT_HEIGHT_A;
	ipipeif_set_format(sd, fh->pad, &format);

	ipipeif_set_default_config(ipipeif);

	return 0;
}