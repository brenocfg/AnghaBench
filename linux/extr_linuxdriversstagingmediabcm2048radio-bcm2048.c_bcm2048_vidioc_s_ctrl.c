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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct file {int dummy; } ;
struct bcm2048_device {int /*<<< orphan*/  power_state; } ;

/* Variables and functions */
 int ENODEV ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 int bcm2048_deinit (struct bcm2048_device*) ; 
 int bcm2048_init (struct bcm2048_device*) ; 
 int bcm2048_set_mute (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct bcm2048_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_vidioc_s_ctrl(struct file *file, void *priv,
				 struct v4l2_control *ctrl)
{
	struct bcm2048_device *bdev = video_get_drvdata(video_devdata(file));
	int err = 0;

	if (!bdev)
		return -ENODEV;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (ctrl->value) {
			if (bdev->power_state) {
				err = bcm2048_set_mute(bdev, ctrl->value);
				err |= bcm2048_deinit(bdev);
			}
		} else {
			if (!bdev->power_state) {
				err = bcm2048_init(bdev);
				err |= bcm2048_set_mute(bdev, ctrl->value);
			}
		}
		break;
	}

	return err;
}