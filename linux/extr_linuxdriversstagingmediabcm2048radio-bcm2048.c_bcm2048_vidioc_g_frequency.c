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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct bcm2048_device {int /*<<< orphan*/  power_state; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int bcm2048_get_fm_frequency (struct bcm2048_device*) ; 
 int /*<<< orphan*/  dev_to_v4l2 (int) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct bcm2048_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_vidioc_g_frequency(struct file *file, void *priv,
				      struct v4l2_frequency *freq)
{
	struct bcm2048_device *bdev = video_get_drvdata(video_devdata(file));
	int err = 0;
	int f;

	if (!bdev->power_state)
		return -ENODEV;

	freq->type = V4L2_TUNER_RADIO;
	f = bcm2048_get_fm_frequency(bdev);

	if (f < 0)
		err = f;
	else
		freq->frequency = dev_to_v4l2(f);

	return err;
}