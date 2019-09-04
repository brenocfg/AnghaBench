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
struct platform_device {int num_resources; struct resource* resource; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int resource_type (struct resource*) ; 

__attribute__((used)) static struct resource *get_platform_resource(struct vfio_platform_device *vdev,
					      int num)
{
	struct platform_device *dev = (struct platform_device *) vdev->opaque;
	int i;

	for (i = 0; i < dev->num_resources; i++) {
		struct resource *r = &dev->resource[i];

		if (resource_type(r) & (IORESOURCE_MEM|IORESOURCE_IO)) {
			if (!num)
				return r;

			num--;
		}
	}
	return NULL;
}