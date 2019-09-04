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
struct TYPE_3__ {struct media_device* mdev; } ;
struct media_entity {TYPE_1__ graph_obj; } ;
struct TYPE_4__ {struct media_entity entity; } ;
struct vpfe_pipeline {scalar_t__ output_num; struct vpfe_video_device** outputs; scalar_t__ input_num; struct vpfe_video_device** inputs; } ;
struct vpfe_video_device {scalar_t__ type; TYPE_2__ video_dev; struct vpfe_pipeline pipe; } ;
struct media_graph {int dummy; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  is_media_entity_v4l2_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  media_entity_to_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  media_graph_walk_cleanup (struct media_graph*) ; 
 int media_graph_walk_init (struct media_graph*,struct media_device*) ; 
 struct media_entity* media_graph_walk_next (struct media_graph*) ; 
 int /*<<< orphan*/  media_graph_walk_start (struct media_graph*,struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vpfe_video_device* to_vpfe_video (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_prepare_pipeline(struct vpfe_video_device *video)
{
	struct media_graph graph;
	struct media_entity *entity = &video->video_dev.entity;
	struct media_device *mdev = entity->graph_obj.mdev;
	struct vpfe_pipeline *pipe = &video->pipe;
	struct vpfe_video_device *far_end = NULL;
	int ret;

	pipe->input_num = 0;
	pipe->output_num = 0;

	if (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		pipe->inputs[pipe->input_num++] = video;
	else
		pipe->outputs[pipe->output_num++] = video;

	mutex_lock(&mdev->graph_mutex);
	ret = media_graph_walk_init(&graph, mdev);
	if (ret) {
		mutex_unlock(&mdev->graph_mutex);
		return -ENOMEM;
	}
	media_graph_walk_start(&graph, entity);
	while ((entity = media_graph_walk_next(&graph))) {
		if (entity == &video->video_dev.entity)
			continue;
		if (!is_media_entity_v4l2_video_device(entity))
			continue;
		far_end = to_vpfe_video(media_entity_to_video_device(entity));
		if (far_end->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			pipe->inputs[pipe->input_num++] = far_end;
		else
			pipe->outputs[pipe->output_num++] = far_end;
	}
	media_graph_walk_cleanup(&graph);
	mutex_unlock(&mdev->graph_mutex);

	return 0;
}