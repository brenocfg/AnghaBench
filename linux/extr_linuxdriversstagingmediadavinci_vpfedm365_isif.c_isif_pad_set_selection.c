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
struct TYPE_4__ {scalar_t__ top; scalar_t__ left; scalar_t__ width; scalar_t__ height; } ;
struct vpfe_isif_device {TYPE_2__ crop; TYPE_1__* formats; } ;
struct v4l2_subdev_selection {size_t pad; scalar_t__ target; int /*<<< orphan*/  which; TYPE_2__ r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t ISIF_PAD_SINK ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct v4l2_mbus_framefmt* __isif_get_format (struct vpfe_isif_device*,struct v4l2_subdev_pad_config*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isif_set_image_window (struct vpfe_isif_device*) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_rect*,TYPE_2__*,int) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,size_t) ; 

__attribute__((used)) static int
isif_pad_set_selection(struct v4l2_subdev *sd,
		       struct v4l2_subdev_pad_config *cfg,
		       struct v4l2_subdev_selection *sel)
{
	struct vpfe_isif_device *vpfe_isif = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	/* check whether it's a valid pad and target */
	if (sel->pad != ISIF_PAD_SINK || sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	format = __isif_get_format(vpfe_isif, cfg, sel->pad, sel->which);
	if (format == NULL)
		return -EINVAL;

	/* check wether crop rect is within limits */
	if (sel->r.top < 0 || sel->r.left < 0 ||
		(sel->r.left + sel->r.width >
		vpfe_isif->formats[ISIF_PAD_SINK].width) ||
		(sel->r.top + sel->r.height >
			vpfe_isif->formats[ISIF_PAD_SINK].height)) {
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = format->width;
		sel->r.height = format->height;
	}
	/* adjust the width to 16 pixel boundary */
	sel->r.width = (sel->r.width + 15) & ~0xf;
	vpfe_isif->crop = sel->r;
	if (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		isif_set_image_window(vpfe_isif);
	} else {
		struct v4l2_rect *rect;

		rect = v4l2_subdev_get_try_crop(sd, cfg, ISIF_PAD_SINK);
		memcpy(rect, &vpfe_isif->crop, sizeof(*rect));
	}
	return 0;
}