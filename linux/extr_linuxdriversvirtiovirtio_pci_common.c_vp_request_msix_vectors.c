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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct virtio_pci_device {int msix_vectors; int msix_enabled; unsigned int msix_used_vectors; unsigned int (* config_vector ) (struct virtio_pci_device*,unsigned int) ;int /*<<< orphan*/ * msix_names; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/ * msix_affinity_masks; TYPE_1__ vdev; } ;
struct virtio_device {int dummy; } ;
struct irq_affinity {int /*<<< orphan*/  pre_vectors; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PCI_IRQ_AFFINITY ; 
 unsigned int PCI_IRQ_MSIX ; 
 unsigned int VIRTIO_MSI_NO_VECTOR ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors_affinity (int /*<<< orphan*/ ,int,int,unsigned int,struct irq_affinity*) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,unsigned int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_pci_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 unsigned int stub1 (struct virtio_pci_device*,unsigned int) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 
 int /*<<< orphan*/  vp_config_changed ; 
 int /*<<< orphan*/  vp_vring_interrupt ; 

__attribute__((used)) static int vp_request_msix_vectors(struct virtio_device *vdev, int nvectors,
				   bool per_vq_vectors, struct irq_affinity *desc)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	const char *name = dev_name(&vp_dev->vdev.dev);
	unsigned flags = PCI_IRQ_MSIX;
	unsigned i, v;
	int err = -ENOMEM;

	vp_dev->msix_vectors = nvectors;

	vp_dev->msix_names = kmalloc_array(nvectors,
					   sizeof(*vp_dev->msix_names),
					   GFP_KERNEL);
	if (!vp_dev->msix_names)
		goto error;
	vp_dev->msix_affinity_masks
		= kcalloc(nvectors, sizeof(*vp_dev->msix_affinity_masks),
			  GFP_KERNEL);
	if (!vp_dev->msix_affinity_masks)
		goto error;
	for (i = 0; i < nvectors; ++i)
		if (!alloc_cpumask_var(&vp_dev->msix_affinity_masks[i],
					GFP_KERNEL))
			goto error;

	if (desc) {
		flags |= PCI_IRQ_AFFINITY;
		desc->pre_vectors++; /* virtio config vector */
	}

	err = pci_alloc_irq_vectors_affinity(vp_dev->pci_dev, nvectors,
					     nvectors, flags, desc);
	if (err < 0)
		goto error;
	vp_dev->msix_enabled = 1;

	/* Set the vector used for configuration */
	v = vp_dev->msix_used_vectors;
	snprintf(vp_dev->msix_names[v], sizeof *vp_dev->msix_names,
		 "%s-config", name);
	err = request_irq(pci_irq_vector(vp_dev->pci_dev, v),
			  vp_config_changed, 0, vp_dev->msix_names[v],
			  vp_dev);
	if (err)
		goto error;
	++vp_dev->msix_used_vectors;

	v = vp_dev->config_vector(vp_dev, v);
	/* Verify we had enough resources to assign the vector */
	if (v == VIRTIO_MSI_NO_VECTOR) {
		err = -EBUSY;
		goto error;
	}

	if (!per_vq_vectors) {
		/* Shared vector for all VQs */
		v = vp_dev->msix_used_vectors;
		snprintf(vp_dev->msix_names[v], sizeof *vp_dev->msix_names,
			 "%s-virtqueues", name);
		err = request_irq(pci_irq_vector(vp_dev->pci_dev, v),
				  vp_vring_interrupt, 0, vp_dev->msix_names[v],
				  vp_dev);
		if (err)
			goto error;
		++vp_dev->msix_used_vectors;
	}
	return 0;
error:
	return err;
}