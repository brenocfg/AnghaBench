#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; } ;
struct most_video_dev {TYPE_1__* vdev; TYPE_5__ v4l2_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * lock; TYPE_5__* v4l2_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 TYPE_1__ comp_videodev_template ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_5__*,char*,int) ; 
 TYPE_1__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (TYPE_1__*) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct most_video_dev*) ; 

__attribute__((used)) static int comp_register_videodev(struct most_video_dev *mdev)
{
	int ret;

	init_waitqueue_head(&mdev->wait_data);

	/* allocate and fill v4l2 video struct */
	mdev->vdev = video_device_alloc();
	if (!mdev->vdev)
		return -ENOMEM;

	/* Fill the video capture device struct */
	*mdev->vdev = comp_videodev_template;
	mdev->vdev->v4l2_dev = &mdev->v4l2_dev;
	mdev->vdev->lock = &mdev->lock;
	snprintf(mdev->vdev->name, sizeof(mdev->vdev->name), "MOST: %s",
		 mdev->v4l2_dev.name);

	/* Register the v4l2 device */
	video_set_drvdata(mdev->vdev, mdev);
	ret = video_register_device(mdev->vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		v4l2_err(&mdev->v4l2_dev, "video_register_device failed (%d)\n",
			 ret);
		video_device_release(mdev->vdev);
	}

	return ret;
}