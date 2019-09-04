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
struct vfio_pci_device {TYPE_1__* ctx; int /*<<< orphan*/  virq_disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_signal (int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_intx (struct vfio_pci_device*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void vfio_send_intx_eventfd(void *opaque, void *unused)
{
	struct vfio_pci_device *vdev = opaque;

	if (likely(is_intx(vdev) && !vdev->virq_disabled))
		eventfd_signal(vdev->ctx[0].trigger, 1);
}