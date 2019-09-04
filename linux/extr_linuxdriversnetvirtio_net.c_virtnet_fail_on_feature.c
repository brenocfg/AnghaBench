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
struct virtio_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/  virtio_has_feature (struct virtio_device*,unsigned int) ; 

__attribute__((used)) static bool virtnet_fail_on_feature(struct virtio_device *vdev,
				    unsigned int fbit,
				    const char *fname, const char *dname)
{
	if (!virtio_has_feature(vdev, fbit))
		return false;

	dev_err(&vdev->dev, "device advertises feature %s but not %s",
		fname, dname);

	return true;
}