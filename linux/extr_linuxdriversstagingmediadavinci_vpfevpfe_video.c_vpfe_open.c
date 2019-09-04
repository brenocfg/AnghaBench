#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vpfe_video_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  usrs; int /*<<< orphan*/  initialized; int /*<<< orphan*/  video_dev; } ;
struct vpfe_fh {int /*<<< orphan*/  vfh; struct vpfe_video_device* video; scalar_t__ io_allowed; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vpfe_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 
 scalar_t__ vpfe_update_pipe_state (struct vpfe_video_device*) ; 

__attribute__((used)) static int vpfe_open(struct file *file)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_fh *handle;

	/* Allocate memory for the file handle object */
	handle = kzalloc(sizeof(struct vpfe_fh), GFP_KERNEL);

	if (!handle)
		return -ENOMEM;

	v4l2_fh_init(&handle->vfh, &video->video_dev);
	v4l2_fh_add(&handle->vfh);

	mutex_lock(&video->lock);
	/* If decoder is not initialized. initialize it */
	if (!video->initialized && vpfe_update_pipe_state(video)) {
		mutex_unlock(&video->lock);
		return -ENODEV;
	}
	/* Increment device users counter */
	video->usrs++;
	/* Set io_allowed member to false */
	handle->io_allowed = 0;
	handle->video = video;
	file->private_data = &handle->vfh;
	mutex_unlock(&video->lock);

	return 0;
}