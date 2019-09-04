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
typedef  int uint32_t ;
struct vfio_platform_device {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  VFIO_IRQ_SET_ACTION_MASK 130 
#define  VFIO_IRQ_SET_ACTION_TRIGGER 129 
 int VFIO_IRQ_SET_ACTION_TYPE_MASK ; 
#define  VFIO_IRQ_SET_ACTION_UNMASK 128 
 int vfio_platform_set_irq_mask (struct vfio_platform_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int vfio_platform_set_irq_trigger (struct vfio_platform_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 
 int vfio_platform_set_irq_unmask (struct vfio_platform_device*,unsigned int,unsigned int,unsigned int,int,void*) ; 

int vfio_platform_set_irqs_ioctl(struct vfio_platform_device *vdev,
				 uint32_t flags, unsigned index, unsigned start,
				 unsigned count, void *data)
{
	int (*func)(struct vfio_platform_device *vdev, unsigned index,
		    unsigned start, unsigned count, uint32_t flags,
		    void *data) = NULL;

	switch (flags & VFIO_IRQ_SET_ACTION_TYPE_MASK) {
	case VFIO_IRQ_SET_ACTION_MASK:
		func = vfio_platform_set_irq_mask;
		break;
	case VFIO_IRQ_SET_ACTION_UNMASK:
		func = vfio_platform_set_irq_unmask;
		break;
	case VFIO_IRQ_SET_ACTION_TRIGGER:
		func = vfio_platform_set_irq_trigger;
		break;
	}

	if (!func)
		return -ENOTTY;

	return func(vdev, index, start, count, flags, data);
}