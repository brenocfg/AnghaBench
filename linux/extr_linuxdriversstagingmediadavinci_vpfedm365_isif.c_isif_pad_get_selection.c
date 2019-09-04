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
struct vpfe_isif_device {int /*<<< orphan*/  crop; } ;
struct v4l2_subdev_selection {scalar_t__ pad; scalar_t__ target; scalar_t__ which; int /*<<< orphan*/  r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ISIF_PAD_SINK ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct v4l2_rect*,int) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

__attribute__((used)) static int
isif_pad_get_selection(struct v4l2_subdev *sd,
		       struct v4l2_subdev_pad_config *cfg,
		       struct v4l2_subdev_selection *sel)
{
	struct vpfe_isif_device *vpfe_isif = v4l2_get_subdevdata(sd);

	/* check whether it's a valid pad and target */
	if (sel->pad != ISIF_PAD_SINK || sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	if (sel->which == V4L2_SUBDEV_FORMAT_TRY) {
		struct v4l2_rect *rect;

		rect = v4l2_subdev_get_try_crop(sd, cfg, ISIF_PAD_SINK);
		memcpy(&sel->r, rect, sizeof(*rect));
	} else {
		sel->r = vpfe_isif->crop;
	}

	return 0;
}