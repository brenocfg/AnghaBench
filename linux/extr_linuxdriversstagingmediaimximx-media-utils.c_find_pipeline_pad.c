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
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {int num_pads; struct media_pad* pads; } ;
struct imx_media_dev {int dummy; } ;

/* Variables and functions */
 int MEDIA_PAD_FL_SINK ; 
 int MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 

__attribute__((used)) static struct media_pad *
find_pipeline_pad(struct imx_media_dev *imxmd,
		  struct media_entity *start_entity,
		  u32 grp_id, bool upstream)
{
	struct media_entity *me = start_entity;
	struct media_pad *pad = NULL;
	struct v4l2_subdev *sd;
	int i;

	for (i = 0; i < me->num_pads; i++) {
		struct media_pad *spad = &me->pads[i];

		if ((upstream && !(spad->flags & MEDIA_PAD_FL_SINK)) ||
		    (!upstream && !(spad->flags & MEDIA_PAD_FL_SOURCE)))
			continue;

		pad = media_entity_remote_pad(spad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			continue;

		if (grp_id != 0) {
			sd = media_entity_to_v4l2_subdev(pad->entity);
			if (sd->grp_id & grp_id)
				return pad;

			return find_pipeline_pad(imxmd, pad->entity,
						 grp_id, upstream);
		} else {
			return pad;
		}
	}

	return NULL;
}