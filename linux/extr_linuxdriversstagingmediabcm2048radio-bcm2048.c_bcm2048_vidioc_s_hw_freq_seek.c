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
struct v4l2_hw_freq_seek {scalar_t__ tuner; scalar_t__ type; int /*<<< orphan*/  seek_upward; } ;
struct file {int dummy; } ;
struct bcm2048_device {int /*<<< orphan*/  power_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_FM_AUTO_SEARCH_MODE ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int bcm2048_set_fm_search_mode_direction (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_fm_search_tune_mode (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct bcm2048_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_vidioc_s_hw_freq_seek(struct file *file, void *priv,
					 const struct v4l2_hw_freq_seek *seek)
{
	struct bcm2048_device *bdev = video_get_drvdata(video_devdata(file));
	int err;

	if (!bdev->power_state)
		return -ENODEV;

	if ((seek->tuner != 0) || (seek->type != V4L2_TUNER_RADIO))
		return -EINVAL;

	err = bcm2048_set_fm_search_mode_direction(bdev, seek->seek_upward);
	err |= bcm2048_set_fm_search_tune_mode(bdev,
					       BCM2048_FM_AUTO_SEARCH_MODE);

	return err;
}