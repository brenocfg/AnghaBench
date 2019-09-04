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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_register_region {int /*<<< orphan*/  (* read ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* uaccess_read ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ;} ;
struct vgic_io_device {struct kvm_vcpu* redist_vcpu; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_io_device {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 struct vgic_io_device* kvm_to_vgic_iodev (struct kvm_io_device*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 struct vgic_register_region* vgic_get_mmio_region (struct kvm_vcpu*,struct vgic_io_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vgic_uaccess_read(struct kvm_vcpu *vcpu, struct kvm_io_device *dev,
			     gpa_t addr, u32 *val)
{
	struct vgic_io_device *iodev = kvm_to_vgic_iodev(dev);
	const struct vgic_register_region *region;
	struct kvm_vcpu *r_vcpu;

	region = vgic_get_mmio_region(vcpu, iodev, addr, sizeof(u32));
	if (!region) {
		*val = 0;
		return 0;
	}

	r_vcpu = iodev->redist_vcpu ? iodev->redist_vcpu : vcpu;
	if (region->uaccess_read)
		*val = region->uaccess_read(r_vcpu, addr, sizeof(u32));
	else
		*val = region->read(r_vcpu, addr, sizeof(u32));

	return 0;
}