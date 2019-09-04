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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct media_entity {int dummy; } ;
struct imx_media_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct v4l2_subdev* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* find_upstream_subdev (struct imx_media_dev*,struct media_entity*,int /*<<< orphan*/ ) ; 

struct v4l2_subdev *
imx_media_find_upstream_subdev(struct imx_media_dev *imxmd,
			       struct media_entity *start_entity,
			       u32 grp_id)
{
	struct v4l2_subdev *sd;

	sd = find_upstream_subdev(imxmd, start_entity, grp_id);
	if (!sd)
		return ERR_PTR(-ENODEV);

	return sd;
}