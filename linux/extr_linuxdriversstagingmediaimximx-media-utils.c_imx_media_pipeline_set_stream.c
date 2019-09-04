#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct media_entity {scalar_t__ pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  graph_mutex; } ;
struct imx_media_dev {TYPE_1__ md; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int EINVAL ; 
 int __media_pipeline_start (struct media_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __media_pipeline_stop (struct media_entity*) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

int imx_media_pipeline_set_stream(struct imx_media_dev *imxmd,
				  struct media_entity *entity,
				  bool on)
{
	struct v4l2_subdev *sd;
	int ret = 0;

	if (!is_media_entity_v4l2_subdev(entity))
		return -EINVAL;
	sd = media_entity_to_v4l2_subdev(entity);

	mutex_lock(&imxmd->md.graph_mutex);

	if (on) {
		ret = __media_pipeline_start(entity, &imxmd->pipe);
		if (ret)
			goto out;
		ret = v4l2_subdev_call(sd, video, s_stream, 1);
		if (ret)
			__media_pipeline_stop(entity);
	} else {
		v4l2_subdev_call(sd, video, s_stream, 0);
		if (entity->pipe)
			__media_pipeline_stop(entity);
	}

out:
	mutex_unlock(&imxmd->md.graph_mutex);
	return ret;
}