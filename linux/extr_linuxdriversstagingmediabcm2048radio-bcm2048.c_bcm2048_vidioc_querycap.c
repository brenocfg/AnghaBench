#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct bcm2048_device {TYPE_1__* client; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_DRIVER_CARD ; 
 int /*<<< orphan*/  BCM2048_DRIVER_NAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_HW_FREQ_SEEK ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct bcm2048_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_vidioc_querycap(struct file *file, void *priv,
				   struct v4l2_capability *capability)
{
	struct bcm2048_device *bdev = video_get_drvdata(video_devdata(file));

	strlcpy(capability->driver, BCM2048_DRIVER_NAME,
		sizeof(capability->driver));
	strlcpy(capability->card, BCM2048_DRIVER_CARD,
		sizeof(capability->card));
	snprintf(capability->bus_info, 32, "I2C: 0x%X", bdev->client->addr);
	capability->device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO |
					V4L2_CAP_HW_FREQ_SEEK;
	capability->capabilities = capability->device_caps |
		V4L2_CAP_DEVICE_CAPS;

	return 0;
}