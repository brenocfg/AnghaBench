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
struct TYPE_3__ {int minor; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; int /*<<< orphan*/ * lock; scalar_t__ tvnorms; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  release; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct vpfe_video_device {int type; TYPE_1__ video_dev; TYPE_2__ pad; int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 128 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct vpfe_video_device*) ; 
 int /*<<< orphan*/  vpfe_fops ; 
 int /*<<< orphan*/  vpfe_ioctl_ops ; 

int vpfe_video_init(struct vpfe_video_device *video, const char *name)
{
	const char *direction;
	int ret;

	switch (video->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		direction = "output";
		video->pad.flags = MEDIA_PAD_FL_SINK;
		video->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		break;

	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		direction = "input";
		video->pad.flags = MEDIA_PAD_FL_SOURCE;
		video->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		break;

	default:
		return -EINVAL;
	}
	/* Initialize field of video device */
	mutex_init(&video->lock);
	video->video_dev.release = video_device_release;
	video->video_dev.fops = &vpfe_fops;
	video->video_dev.ioctl_ops = &vpfe_ioctl_ops;
	video->video_dev.minor = -1;
	video->video_dev.tvnorms = 0;
	video->video_dev.lock = &video->lock;
	snprintf(video->video_dev.name, sizeof(video->video_dev.name),
		 "DAVINCI VIDEO %s %s", name, direction);

	spin_lock_init(&video->irqlock);
	spin_lock_init(&video->dma_queue_lock);
	ret = media_entity_pads_init(&video->video_dev.entity,
				1, &video->pad);
	if (ret < 0)
		return ret;

	video_set_drvdata(&video->video_dev, video);

	return 0;
}