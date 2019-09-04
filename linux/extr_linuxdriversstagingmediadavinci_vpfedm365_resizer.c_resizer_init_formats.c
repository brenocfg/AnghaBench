#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_7__ {struct v4l2_subdev subdev; } ;
struct TYPE_6__ {struct v4l2_subdev subdev; } ;
struct TYPE_5__ {struct v4l2_subdev subdev; } ;
struct vpfe_resizer_device {TYPE_3__ resizer_b; TYPE_2__ resizer_a; TYPE_1__ crop_resizer; } ;
struct TYPE_8__ {void* height; void* width; void* code; } ;
struct v4l2_subdev_format {TYPE_4__ format; void* which; void* pad; } ;
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
typedef  int /*<<< orphan*/  format ;
typedef  void* __u32 ;

/* Variables and functions */
 void* IPIPE_MAX_OUTPUT_HEIGHT_A ; 
 void* IPIPE_MAX_OUTPUT_HEIGHT_B ; 
 void* IPIPE_MAX_OUTPUT_WIDTH_A ; 
 void* IPIPE_MAX_OUTPUT_WIDTH_B ; 
 void* MAX_IN_HEIGHT ; 
 void* MAX_IN_WIDTH ; 
 void* MEDIA_BUS_FMT_UYVY8_2X8 ; 
 void* MEDIA_BUS_FMT_YUYV8_2X8 ; 
 void* RESIZER_CROP_PAD_SINK ; 
 void* RESIZER_CROP_PAD_SOURCE ; 
 void* RESIZER_CROP_PAD_SOURCE2 ; 
 void* RESIZER_PAD_SINK ; 
 void* RESIZER_PAD_SOURCE ; 
 void* V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resizer_set_format (struct v4l2_subdev*,int /*<<< orphan*/ ,struct v4l2_subdev_format*) ; 
 struct vpfe_resizer_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_init_formats(struct v4l2_subdev *sd,
				struct v4l2_subdev_fh *fh)
{
	__u32 which = V4L2_SUBDEV_FORMAT_TRY;
	struct vpfe_resizer_device *resizer = v4l2_get_subdevdata(sd);
	struct v4l2_subdev_format format;

	if (&resizer->crop_resizer.subdev == sd) {
		memset(&format, 0, sizeof(format));
		format.pad = RESIZER_CROP_PAD_SINK;
		format.which = which;
		format.format.code = MEDIA_BUS_FMT_YUYV8_2X8;
		format.format.width = MAX_IN_WIDTH;
		format.format.height = MAX_IN_HEIGHT;
		resizer_set_format(sd, fh->pad, &format);

		memset(&format, 0, sizeof(format));
		format.pad = RESIZER_CROP_PAD_SOURCE;
		format.which = which;
		format.format.code = MEDIA_BUS_FMT_UYVY8_2X8;
		format.format.width = MAX_IN_WIDTH;
		format.format.height = MAX_IN_WIDTH;
		resizer_set_format(sd, fh->pad, &format);

		memset(&format, 0, sizeof(format));
		format.pad = RESIZER_CROP_PAD_SOURCE2;
		format.which = which;
		format.format.code = MEDIA_BUS_FMT_UYVY8_2X8;
		format.format.width = MAX_IN_WIDTH;
		format.format.height = MAX_IN_WIDTH;
		resizer_set_format(sd, fh->pad, &format);
	} else if (&resizer->resizer_a.subdev == sd) {
		memset(&format, 0, sizeof(format));
		format.pad = RESIZER_PAD_SINK;
		format.which = which;
		format.format.code = MEDIA_BUS_FMT_YUYV8_2X8;
		format.format.width = MAX_IN_WIDTH;
		format.format.height = MAX_IN_HEIGHT;
		resizer_set_format(sd, fh->pad, &format);

		memset(&format, 0, sizeof(format));
		format.pad = RESIZER_PAD_SOURCE;
		format.which = which;
		format.format.code = MEDIA_BUS_FMT_UYVY8_2X8;
		format.format.width = IPIPE_MAX_OUTPUT_WIDTH_A;
		format.format.height = IPIPE_MAX_OUTPUT_HEIGHT_A;
		resizer_set_format(sd, fh->pad, &format);
	} else if (&resizer->resizer_b.subdev == sd) {
		memset(&format, 0, sizeof(format));
		format.pad = RESIZER_PAD_SINK;
		format.which = which;
		format.format.code = MEDIA_BUS_FMT_YUYV8_2X8;
		format.format.width = MAX_IN_WIDTH;
		format.format.height = MAX_IN_HEIGHT;
		resizer_set_format(sd, fh->pad, &format);

		memset(&format, 0, sizeof(format));
		format.pad = RESIZER_PAD_SOURCE;
		format.which = which;
		format.format.code = MEDIA_BUS_FMT_UYVY8_2X8;
		format.format.width = IPIPE_MAX_OUTPUT_WIDTH_B;
		format.format.height = IPIPE_MAX_OUTPUT_HEIGHT_B;
		resizer_set_format(sd, fh->pad, &format);
	}

	return 0;
}