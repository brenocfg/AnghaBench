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
struct vfio_platform_device {scalar_t__ opaque; } ;
struct resource {int dummy; } ;
struct amba_device {struct resource res; } ;

/* Variables and functions */

__attribute__((used)) static struct resource *get_amba_resource(struct vfio_platform_device *vdev,
					  int i)
{
	struct amba_device *adev = (struct amba_device *) vdev->opaque;

	if (i == 0)
		return &adev->res;

	return NULL;
}