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
struct vgic_io_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  regions; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int SZ_64K ; 
 int /*<<< orphan*/  kvm_io_gic_ops ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_v3_dist_registers ; 

unsigned int vgic_v3_init_dist_iodev(struct vgic_io_device *dev)
{
	dev->regions = vgic_v3_dist_registers;
	dev->nr_regions = ARRAY_SIZE(vgic_v3_dist_registers);

	kvm_iodevice_init(&dev->dev, &kvm_io_gic_ops);

	return SZ_64K;
}