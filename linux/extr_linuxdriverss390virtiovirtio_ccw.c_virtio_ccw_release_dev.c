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
struct virtio_device {int dummy; } ;
struct virtio_ccw_device {struct virtio_ccw_device* config_block; struct virtio_ccw_device* status; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct virtio_device* dev_to_virtio (struct device*) ; 
 int /*<<< orphan*/  kfree (struct virtio_ccw_device*) ; 
 struct virtio_ccw_device* to_vc_device (struct virtio_device*) ; 

__attribute__((used)) static void virtio_ccw_release_dev(struct device *_d)
{
	struct virtio_device *dev = dev_to_virtio(_d);
	struct virtio_ccw_device *vcdev = to_vc_device(dev);

	kfree(vcdev->status);
	kfree(vcdev->config_block);
	kfree(vcdev);
}