#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_pipeline {scalar_t__ state; int /*<<< orphan*/  graph; TYPE_2__** inputs; int /*<<< orphan*/ * outputs; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_6__ {struct media_device* mdev; } ;
struct media_entity {TYPE_3__ graph_obj; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;
struct TYPE_4__ {struct media_entity entity; } ;
struct TYPE_5__ {TYPE_1__ video_dev; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int ETIMEDOUT ; 
 scalar_t__ VPFE_PIPELINE_STREAM_CONTINUOUS ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  media_graph_walk_cleanup (int /*<<< orphan*/ *) ; 
 struct media_entity* media_graph_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_graph_walk_start (int /*<<< orphan*/ *,struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 struct media_entity* vpfe_get_input_entity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_pipeline_disable(struct vpfe_pipeline *pipe)
{
	struct media_entity *entity;
	struct v4l2_subdev *subdev;
	struct media_device *mdev;
	int ret = 0;

	if (pipe->state == VPFE_PIPELINE_STREAM_CONTINUOUS)
		entity = vpfe_get_input_entity(pipe->outputs[0]);
	else
		entity = &pipe->inputs[0]->video_dev.entity;

	mdev = entity->graph_obj.mdev;
	mutex_lock(&mdev->graph_mutex);
	media_graph_walk_start(&pipe->graph, entity);

	while ((entity = media_graph_walk_next(&pipe->graph))) {

		if (!is_media_entity_v4l2_subdev(entity))
			continue;
		subdev = media_entity_to_v4l2_subdev(entity);
		ret = v4l2_subdev_call(subdev, video, s_stream, 0);
		if (ret < 0 && ret != -ENOIOCTLCMD)
			break;
	}
	mutex_unlock(&mdev->graph_mutex);

	media_graph_walk_cleanup(&pipe->graph);
	return ret ? -ETIMEDOUT : 0;
}