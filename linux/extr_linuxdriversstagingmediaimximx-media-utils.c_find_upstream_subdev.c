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
typedef  int u32 ;
struct v4l2_subdev {int grp_id; } ;
struct media_pad {struct media_entity* entity; } ;
struct media_entity {int dummy; } ;
struct imx_media_dev {int dummy; } ;

/* Variables and functions */
 struct media_pad* find_pipeline_pad (struct imx_media_dev*,struct media_entity*,int,int) ; 
 scalar_t__ is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 

__attribute__((used)) static struct v4l2_subdev *
find_upstream_subdev(struct imx_media_dev *imxmd,
		     struct media_entity *start_entity,
		     u32 grp_id)
{
	struct v4l2_subdev *sd;
	struct media_pad *pad;

	if (is_media_entity_v4l2_subdev(start_entity)) {
		sd = media_entity_to_v4l2_subdev(start_entity);
		if (sd->grp_id & grp_id)
			return sd;
	}

	pad = find_pipeline_pad(imxmd, start_entity, grp_id, true);

	return pad ? media_entity_to_v4l2_subdev(pad->entity) : NULL;
}