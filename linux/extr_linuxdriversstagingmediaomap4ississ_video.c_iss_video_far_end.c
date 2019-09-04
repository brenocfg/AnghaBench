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
struct media_graph {int dummy; } ;
struct TYPE_3__ {struct media_device* mdev; } ;
struct media_entity {TYPE_1__ graph_obj; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;
struct TYPE_4__ {struct media_entity entity; } ;
struct iss_video {scalar_t__ type; TYPE_2__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_media_entity_v4l2_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  media_entity_to_video_device (struct media_entity*) ; 
 int /*<<< orphan*/  media_graph_walk_cleanup (struct media_graph*) ; 
 scalar_t__ media_graph_walk_init (struct media_graph*,struct media_device*) ; 
 struct media_entity* media_graph_walk_next (struct media_graph*) ; 
 int /*<<< orphan*/  media_graph_walk_start (struct media_graph*,struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iss_video* to_iss_video (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iss_video *
iss_video_far_end(struct iss_video *video)
{
	struct media_graph graph;
	struct media_entity *entity = &video->video.entity;
	struct media_device *mdev = entity->graph_obj.mdev;
	struct iss_video *far_end = NULL;

	mutex_lock(&mdev->graph_mutex);

	if (media_graph_walk_init(&graph, mdev)) {
		mutex_unlock(&mdev->graph_mutex);
		return NULL;
	}

	media_graph_walk_start(&graph, entity);

	while ((entity = media_graph_walk_next(&graph))) {
		if (entity == &video->video.entity)
			continue;

		if (!is_media_entity_v4l2_video_device(entity))
			continue;

		far_end = to_iss_video(media_entity_to_video_device(entity));
		if (far_end->type != video->type)
			break;

		far_end = NULL;
	}

	mutex_unlock(&mdev->graph_mutex);

	media_graph_walk_cleanup(&graph);

	return far_end;
}