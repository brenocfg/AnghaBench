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
struct v4l2_tuner {scalar_t__ index; } ;
struct file {int dummy; } ;
struct bcm2048_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct bcm2048_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_vidioc_s_tuner(struct file *file, void *priv,
				  const struct v4l2_tuner *tuner)
{
	struct bcm2048_device *bdev = video_get_drvdata(video_devdata(file));

	if (!bdev)
		return -ENODEV;

	if (tuner->index > 0)
		return -EINVAL;

	return 0;
}