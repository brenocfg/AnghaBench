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
typedef  int /*<<< orphan*/  u16 ;
struct virtqueue {int dummy; } ;
struct virtio_pci_vq_info {int /*<<< orphan*/  node; struct virtqueue* vq; } ;
struct virtio_pci_device {struct virtio_pci_vq_info** vqs; int /*<<< orphan*/  lock; int /*<<< orphan*/  virtqueues; struct virtqueue* (* setup_vq ) (struct virtio_pci_device*,struct virtio_pci_vq_info*,unsigned int,void (*) (struct virtqueue*),char const*,int,int /*<<< orphan*/ ) ;} ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct virtqueue* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct virtqueue*) ; 
 int /*<<< orphan*/  kfree (struct virtio_pci_vq_info*) ; 
 struct virtio_pci_vq_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virtqueue* stub1 (struct virtio_pci_device*,struct virtio_pci_vq_info*,unsigned int,void (*) (struct virtqueue*),char const*,int,int /*<<< orphan*/ ) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

__attribute__((used)) static struct virtqueue *vp_setup_vq(struct virtio_device *vdev, unsigned index,
				     void (*callback)(struct virtqueue *vq),
				     const char *name,
				     bool ctx,
				     u16 msix_vec)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	struct virtio_pci_vq_info *info = kmalloc(sizeof *info, GFP_KERNEL);
	struct virtqueue *vq;
	unsigned long flags;

	/* fill out our structure that represents an active queue */
	if (!info)
		return ERR_PTR(-ENOMEM);

	vq = vp_dev->setup_vq(vp_dev, info, index, callback, name, ctx,
			      msix_vec);
	if (IS_ERR(vq))
		goto out_info;

	info->vq = vq;
	if (callback) {
		spin_lock_irqsave(&vp_dev->lock, flags);
		list_add(&info->node, &vp_dev->virtqueues);
		spin_unlock_irqrestore(&vp_dev->lock, flags);
	} else {
		INIT_LIST_HEAD(&info->node);
	}

	vp_dev->vqs[index] = info;
	return vq;

out_info:
	kfree(info);
	return vq;
}