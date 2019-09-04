#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct media_graph {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  mdev; } ;
struct media_entity {TYPE_1__ graph_obj; int /*<<< orphan*/  pipe; } ;
struct TYPE_10__ {int /*<<< orphan*/  bytesperline; } ;
struct TYPE_11__ {TYPE_2__ pix; } ;
struct TYPE_12__ {TYPE_3__ fmt; } ;
struct iss_video_fh {int /*<<< orphan*/  queue; int /*<<< orphan*/  timeperframe; TYPE_4__ format; } ;
struct TYPE_13__ {struct media_entity entity; } ;
struct iss_pipeline {int state; int /*<<< orphan*/  ent_enum; struct iss_video* input; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  max_timeperframe; int /*<<< orphan*/  lock; struct iss_video* output; int /*<<< orphan*/  pipe; scalar_t__ external_bpp; scalar_t__ external_rate; int /*<<< orphan*/ * external; } ;
struct iss_video {int type; int bpl_padding; int error; int /*<<< orphan*/  stream_lock; int /*<<< orphan*/ * queue; TYPE_7__* iss; TYPE_5__ video; int /*<<< orphan*/  qlock; int /*<<< orphan*/  dmaqueue_flags; int /*<<< orphan*/  dmaqueue; int /*<<< orphan*/  bpl_value; struct iss_pipeline pipe; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
typedef  enum iss_pipeline_state { ____Placeholder_iss_pipeline_state } iss_pipeline_state ;
struct TYPE_15__ {TYPE_6__* pdata; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* set_constraints ) (TYPE_7__*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ISS_PIPELINE_IDLE_INPUT ; 
 int ISS_PIPELINE_IDLE_OUTPUT ; 
 int ISS_PIPELINE_STREAM ; 
 int /*<<< orphan*/  ISS_PIPELINE_STREAM_CONTINUOUS ; 
 int ISS_PIPELINE_STREAM_INPUT ; 
 int ISS_PIPELINE_STREAM_OUTPUT ; 
 int /*<<< orphan*/  ISS_VIDEO_DMAQUEUE_UNDERRUN ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int iss_video_check_format (struct iss_video*,struct iss_video_fh*) ; 
 struct iss_video* iss_video_far_end (struct iss_video*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_entity_enum_cleanup (int /*<<< orphan*/ *) ; 
 int media_entity_enum_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_enum_set (int /*<<< orphan*/ *,struct media_entity*) ; 
 int /*<<< orphan*/  media_graph_walk_cleanup (struct media_graph*) ; 
 int media_graph_walk_init (struct media_graph*,int /*<<< orphan*/ ) ; 
 struct media_entity* media_graph_walk_next (struct media_graph*) ; 
 int /*<<< orphan*/  media_graph_walk_start (struct media_graph*,struct media_entity*) ; 
 int media_pipeline_start (struct media_entity*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (struct media_entity*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap4iss_pipeline_set_stream (struct iss_pipeline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int) ; 
 struct iss_pipeline* to_iss_pipeline (struct media_entity*) ; 
 struct iss_video_fh* to_iss_video_fh (void*) ; 
 int /*<<< orphan*/  vb2_streamoff (int /*<<< orphan*/ *,int) ; 
 int vb2_streamon (int /*<<< orphan*/ *,int) ; 
 struct iss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
iss_video_streamon(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct iss_video_fh *vfh = to_iss_video_fh(fh);
	struct iss_video *video = video_drvdata(file);
	struct media_graph graph;
	struct media_entity *entity = &video->video.entity;
	enum iss_pipeline_state state;
	struct iss_pipeline *pipe;
	struct iss_video *far_end;
	unsigned long flags;
	int ret;

	if (type != video->type)
		return -EINVAL;

	mutex_lock(&video->stream_lock);

	/*
	 * Start streaming on the pipeline. No link touching an entity in the
	 * pipeline can be activated or deactivated once streaming is started.
	 */
	pipe = entity->pipe
	     ? to_iss_pipeline(entity) : &video->pipe;
	pipe->external = NULL;
	pipe->external_rate = 0;
	pipe->external_bpp = 0;

	ret = media_entity_enum_init(&pipe->ent_enum, entity->graph_obj.mdev);
	if (ret)
		goto err_graph_walk_init;

	ret = media_graph_walk_init(&graph, entity->graph_obj.mdev);
	if (ret)
		goto err_graph_walk_init;

	if (video->iss->pdata->set_constraints)
		video->iss->pdata->set_constraints(video->iss, true);

	ret = media_pipeline_start(entity, &pipe->pipe);
	if (ret < 0)
		goto err_media_pipeline_start;

	media_graph_walk_start(&graph, entity);
	while ((entity = media_graph_walk_next(&graph)))
		media_entity_enum_set(&pipe->ent_enum, entity);

	/*
	 * Verify that the currently configured format matches the output of
	 * the connected subdev.
	 */
	ret = iss_video_check_format(video, vfh);
	if (ret < 0)
		goto err_iss_video_check_format;

	video->bpl_padding = ret;
	video->bpl_value = vfh->format.fmt.pix.bytesperline;

	/*
	 * Find the ISS video node connected at the far end of the pipeline and
	 * update the pipeline.
	 */
	far_end = iss_video_far_end(video);

	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		state = ISS_PIPELINE_STREAM_OUTPUT | ISS_PIPELINE_IDLE_OUTPUT;
		pipe->input = far_end;
		pipe->output = video;
	} else {
		if (!far_end) {
			ret = -EPIPE;
			goto err_iss_video_check_format;
		}

		state = ISS_PIPELINE_STREAM_INPUT | ISS_PIPELINE_IDLE_INPUT;
		pipe->input = video;
		pipe->output = far_end;
	}

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~ISS_PIPELINE_STREAM;
	pipe->state |= state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/*
	 * Set the maximum time per frame as the value requested by userspace.
	 * This is a soft limit that can be overridden if the hardware doesn't
	 * support the request limit.
	 */
	if (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		pipe->max_timeperframe = vfh->timeperframe;

	video->queue = &vfh->queue;
	INIT_LIST_HEAD(&video->dmaqueue);
	video->error = false;
	atomic_set(&pipe->frame_number, -1);

	ret = vb2_streamon(&vfh->queue, type);
	if (ret < 0)
		goto err_iss_video_check_format;

	/*
	 * In sensor-to-memory mode, the stream can be started synchronously
	 * to the stream on command. In memory-to-memory mode, it will be
	 * started when buffers are queued on both the input and output.
	 */
	if (!pipe->input) {
		unsigned long flags;

		ret = omap4iss_pipeline_set_stream(pipe,
					      ISS_PIPELINE_STREAM_CONTINUOUS);
		if (ret < 0)
			goto err_omap4iss_set_stream;
		spin_lock_irqsave(&video->qlock, flags);
		if (list_empty(&video->dmaqueue))
			video->dmaqueue_flags |= ISS_VIDEO_DMAQUEUE_UNDERRUN;
		spin_unlock_irqrestore(&video->qlock, flags);
	}

	media_graph_walk_cleanup(&graph);

	mutex_unlock(&video->stream_lock);

	return 0;

err_omap4iss_set_stream:
	vb2_streamoff(&vfh->queue, type);
err_iss_video_check_format:
	media_pipeline_stop(&video->video.entity);
err_media_pipeline_start:
	if (video->iss->pdata->set_constraints)
		video->iss->pdata->set_constraints(video->iss, false);
	video->queue = NULL;

	media_graph_walk_cleanup(&graph);

err_graph_walk_init:
	media_entity_enum_cleanup(&pipe->ent_enum);

	mutex_unlock(&video->stream_lock);

	return ret;
}