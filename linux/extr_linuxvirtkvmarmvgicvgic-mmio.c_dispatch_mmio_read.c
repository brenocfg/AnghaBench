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
struct vgic_register_region {unsigned long (* read ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ;unsigned long (* its_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct vgic_io_device {int iodev_type; int /*<<< orphan*/  its; struct kvm_vcpu* redist_vcpu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_io_device {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
#define  IODEV_CPUIF 131 
#define  IODEV_DIST 130 
#define  IODEV_ITS 129 
#define  IODEV_REDIST 128 
 struct vgic_io_device* kvm_to_vgic_iodev (struct kvm_io_device*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 unsigned long stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 unsigned long stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 unsigned long stub3 (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 unsigned long stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vgic_data_host_to_mmio_bus (void*,int,unsigned long) ; 
 struct vgic_register_region* vgic_get_mmio_region (struct kvm_vcpu*,struct vgic_io_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dispatch_mmio_read(struct kvm_vcpu *vcpu, struct kvm_io_device *dev,
			      gpa_t addr, int len, void *val)
{
	struct vgic_io_device *iodev = kvm_to_vgic_iodev(dev);
	const struct vgic_register_region *region;
	unsigned long data = 0;

	region = vgic_get_mmio_region(vcpu, iodev, addr, len);
	if (!region) {
		memset(val, 0, len);
		return 0;
	}

	switch (iodev->iodev_type) {
	case IODEV_CPUIF:
		data = region->read(vcpu, addr, len);
		break;
	case IODEV_DIST:
		data = region->read(vcpu, addr, len);
		break;
	case IODEV_REDIST:
		data = region->read(iodev->redist_vcpu, addr, len);
		break;
	case IODEV_ITS:
		data = region->its_read(vcpu->kvm, iodev->its, addr, len);
		break;
	}

	vgic_data_host_to_mmio_bus(val, len, data);
	return 0;
}