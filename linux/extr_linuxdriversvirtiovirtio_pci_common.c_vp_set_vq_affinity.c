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
struct virtqueue {size_t index; int /*<<< orphan*/  callback; struct virtio_device* vdev; } ;
struct virtio_pci_vq_info {size_t msix_vector; } ;
struct virtio_pci_device {int /*<<< orphan*/  pci_dev; struct cpumask** msix_affinity_masks; scalar_t__ msix_enabled; struct virtio_pci_vq_info** vqs; } ;
struct virtio_device {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,struct cpumask const*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (unsigned int,struct cpumask*) ; 
 unsigned int pci_irq_vector (int /*<<< orphan*/ ,size_t) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

int vp_set_vq_affinity(struct virtqueue *vq, const struct cpumask *cpu_mask)
{
	struct virtio_device *vdev = vq->vdev;
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	struct virtio_pci_vq_info *info = vp_dev->vqs[vq->index];
	struct cpumask *mask;
	unsigned int irq;

	if (!vq->callback)
		return -EINVAL;

	if (vp_dev->msix_enabled) {
		mask = vp_dev->msix_affinity_masks[info->msix_vector];
		irq = pci_irq_vector(vp_dev->pci_dev, info->msix_vector);
		if (!cpu_mask)
			irq_set_affinity_hint(irq, NULL);
		else {
			cpumask_copy(mask, cpu_mask);
			irq_set_affinity_hint(irq, mask);
		}
	}
	return 0;
}