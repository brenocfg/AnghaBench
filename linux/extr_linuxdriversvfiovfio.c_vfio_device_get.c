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
struct vfio_device {int /*<<< orphan*/  kref; int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_group_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfio_device_get(struct vfio_device *device)
{
	vfio_group_get(device->group);
	kref_get(&device->kref);
}