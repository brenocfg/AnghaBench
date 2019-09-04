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
struct vpfe_pipeline {int /*<<< orphan*/ * outputs; } ;
struct TYPE_4__ {scalar_t__ code; scalar_t__ width; scalar_t__ height; } ;
struct v4l2_subdev_format {TYPE_2__ format; int /*<<< orphan*/  pad; void* which; } ;
struct TYPE_3__ {struct media_pad* pads; } ;
struct v4l2_subdev {TYPE_1__ entity; } ;
struct media_pad {int flags; int /*<<< orphan*/  index; int /*<<< orphan*/  entity; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int EPIPE ; 
 int MEDIA_PAD_FL_SINK ; 
 void* V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  get_fmt ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (int /*<<< orphan*/ ) ; 
 struct media_pad* media_entity_remote_pad (struct media_pad*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,struct media_pad*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 struct v4l2_subdev* vpfe_video_remote_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vpfe_video_validate_pipeline(struct vpfe_pipeline *pipe)
{
	struct v4l2_subdev_format fmt_source;
	struct v4l2_subdev_format fmt_sink;
	struct v4l2_subdev *subdev;
	struct media_pad *pad;
	int ret;

	/*
	 * Should not matter if it is output[0] or 1 as
	 * the general ideas is to traverse backwards and
	 * the fact that the out video node always has the
	 * format of the connected pad.
	 */
	subdev = vpfe_video_remote_subdev(pipe->outputs[0], NULL);
	if (!subdev)
		return -EPIPE;

	while (1) {
		/* Retrieve the sink format */
		pad = &subdev->entity.pads[0];
		if (!(pad->flags & MEDIA_PAD_FL_SINK))
			break;

		fmt_sink.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		fmt_sink.pad = pad->index;
		ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL,
				       &fmt_sink);

		if (ret < 0 && ret != -ENOIOCTLCMD)
			return -EPIPE;

		/* Retrieve the source format */
		pad = media_entity_remote_pad(pad);
		if (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			break;

		subdev = media_entity_to_v4l2_subdev(pad->entity);

		fmt_source.which = V4L2_SUBDEV_FORMAT_ACTIVE;
		fmt_source.pad = pad->index;
		ret = v4l2_subdev_call(subdev, pad, get_fmt, NULL, &fmt_source);
		if (ret < 0 && ret != -ENOIOCTLCMD)
			return -EPIPE;

		/* Check if the two ends match */
		if (fmt_source.format.code != fmt_sink.format.code ||
		    fmt_source.format.width != fmt_sink.format.width ||
		    fmt_source.format.height != fmt_sink.format.height)
			return -EPIPE;
	}
	return 0;
}