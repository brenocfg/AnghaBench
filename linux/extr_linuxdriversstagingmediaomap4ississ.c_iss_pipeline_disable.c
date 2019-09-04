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
struct v4l2_subdev {int /*<<< orphan*/  entity; int /*<<< orphan*/  name; } ;
struct media_pad {int flags; struct media_entity* entity; } ;
struct media_entity {struct media_pad* pads; } ;
struct iss_pipeline {TYPE_2__* output; } ;
struct iss_device {int /*<<< orphan*/  crashed; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct media_entity entity; } ;
struct TYPE_4__ {TYPE_1__ video; struct iss_device* iss; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  media_entity_enum_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int iss_pipeline_disable(struct iss_pipeline *pipe,
				struct media_entity *until)
{
	struct iss_device *iss = pipe->output->iss;
	struct media_entity *entity;
	struct media_pad *pad;
	struct v4l2_subdev *subdev;
	int failure = 0;
	int ret;

	entity = &pipe->output->video.entity;
	while (1) {
		pad = &entity->pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			break;

		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		entity = pad->entity;
		if (entity == until)
			break;

		subdev = media_entity_to_v4l2_subdev(entity);
		ret = v4l2_subdev_call(subdev, video, s_stream, 0);
		if (ret < 0) {
			dev_warn(iss->dev, "%s: module stop timeout.\n",
				 subdev->name);
			/* If the entity failed to stopped, assume it has
			 * crashed. Mark it as such, the ISS will be reset when
			 * applications will release it.
			 */
			media_entity_enum_set(&iss->crashed, &subdev->entity);
			failure = -ETIMEDOUT;
		}
	}

	return failure;
}