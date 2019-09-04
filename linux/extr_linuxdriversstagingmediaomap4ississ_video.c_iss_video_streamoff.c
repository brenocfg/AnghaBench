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
struct iss_video_fh {int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct iss_video {int type; int /*<<< orphan*/  stream_lock; TYPE_2__ video; TYPE_3__* iss; int /*<<< orphan*/ * queue; } ;
struct iss_pipeline {int state; int /*<<< orphan*/  ent_enum; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
typedef  enum iss_pipeline_state { ____Placeholder_iss_pipeline_state } iss_pipeline_state ;
struct TYPE_6__ {TYPE_1__* pdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_constraints ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ISS_PIPELINE_QUEUE_INPUT ; 
 int ISS_PIPELINE_QUEUE_OUTPUT ; 
 int ISS_PIPELINE_STREAM_INPUT ; 
 int ISS_PIPELINE_STREAM_OUTPUT ; 
 int /*<<< orphan*/  ISS_PIPELINE_STREAM_STOPPED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  media_entity_enum_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap4iss_pipeline_set_stream (struct iss_pipeline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 struct iss_pipeline* to_iss_pipeline (int /*<<< orphan*/ *) ; 
 struct iss_video_fh* to_iss_video_fh (void*) ; 
 int /*<<< orphan*/  vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_streamoff (int /*<<< orphan*/ *,int) ; 
 struct iss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
iss_video_streamoff(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct iss_video_fh *vfh = to_iss_video_fh(fh);
	struct iss_video *video = video_drvdata(file);
	struct iss_pipeline *pipe = to_iss_pipeline(&video->video.entity);
	enum iss_pipeline_state state;
	unsigned long flags;

	if (type != video->type)
		return -EINVAL;

	mutex_lock(&video->stream_lock);

	if (!vb2_is_streaming(&vfh->queue))
		goto done;

	/* Update the pipeline state. */
	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		state = ISS_PIPELINE_STREAM_OUTPUT
		      | ISS_PIPELINE_QUEUE_OUTPUT;
	else
		state = ISS_PIPELINE_STREAM_INPUT
		      | ISS_PIPELINE_QUEUE_INPUT;

	spin_lock_irqsave(&pipe->lock, flags);
	pipe->state &= ~state;
	spin_unlock_irqrestore(&pipe->lock, flags);

	/* Stop the stream. */
	omap4iss_pipeline_set_stream(pipe, ISS_PIPELINE_STREAM_STOPPED);
	vb2_streamoff(&vfh->queue, type);
	video->queue = NULL;

	media_entity_enum_cleanup(&pipe->ent_enum);

	if (video->iss->pdata->set_constraints)
		video->iss->pdata->set_constraints(video->iss, false);
	media_pipeline_stop(&video->video.entity);

done:
	mutex_unlock(&video->stream_lock);
	return 0;
}