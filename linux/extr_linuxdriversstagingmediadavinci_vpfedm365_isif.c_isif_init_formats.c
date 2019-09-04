#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* height; void* width; } ;
struct TYPE_3__ {void* height; void* width; void* code; } ;
struct v4l2_subdev_selection {TYPE_2__ r; int /*<<< orphan*/  target; void* which; void* pad; TYPE_1__ format; } ;
struct v4l2_subdev_format {TYPE_2__ r; int /*<<< orphan*/  target; void* which; void* pad; TYPE_1__ format; } ;
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
typedef  int /*<<< orphan*/  sel ;
typedef  int /*<<< orphan*/  format ;

/* Variables and functions */
 void* ISIF_PAD_SINK ; 
 void* ISIF_PAD_SOURCE ; 
 void* MAX_HEIGHT ; 
 void* MAX_WIDTH ; 
 void* MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 void* V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  isif_pad_set_selection (struct v4l2_subdev*,int /*<<< orphan*/ ,struct v4l2_subdev_selection*) ; 
 int /*<<< orphan*/  isif_set_format (struct v4l2_subdev*,int /*<<< orphan*/ ,struct v4l2_subdev_selection*) ; 
 int /*<<< orphan*/  memset (struct v4l2_subdev_selection*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isif_init_formats(struct v4l2_subdev *sd,
		  struct v4l2_subdev_fh *fh)
{
	struct v4l2_subdev_format format;
	struct v4l2_subdev_selection sel;

	memset(&format, 0, sizeof(format));
	format.pad = ISIF_PAD_SINK;
	format.which = V4L2_SUBDEV_FORMAT_TRY;
	format.format.code = MEDIA_BUS_FMT_SGRBG12_1X12;
	format.format.width = MAX_WIDTH;
	format.format.height = MAX_HEIGHT;
	isif_set_format(sd, fh->pad, &format);

	memset(&format, 0, sizeof(format));
	format.pad = ISIF_PAD_SOURCE;
	format.which = V4L2_SUBDEV_FORMAT_TRY;
	format.format.code = MEDIA_BUS_FMT_SGRBG12_1X12;
	format.format.width = MAX_WIDTH;
	format.format.height = MAX_HEIGHT;
	isif_set_format(sd, fh->pad, &format);

	memset(&sel, 0, sizeof(sel));
	sel.pad = ISIF_PAD_SINK;
	sel.which = V4L2_SUBDEV_FORMAT_TRY;
	sel.target = V4L2_SEL_TGT_CROP;
	sel.r.width = MAX_WIDTH;
	sel.r.height = MAX_HEIGHT;
	isif_pad_set_selection(sd, fh->pad, &sel);

	return 0;
}