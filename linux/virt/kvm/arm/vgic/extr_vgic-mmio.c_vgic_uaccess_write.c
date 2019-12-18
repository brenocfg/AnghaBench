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
struct vgic_register_region {int (* uaccess_write ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* write ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ;} ;
struct vgic_io_device {struct kvm_vcpu* redist_vcpu; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_io_device {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 struct vgic_io_device* kvm_to_vgic_iodev (struct kvm_io_device*) ; 
 int stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ; 
 struct vgic_register_region* vgic_get_mmio_region (struct kvm_vcpu*,struct vgic_io_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vgic_uaccess_write(struct kvm_vcpu *vcpu, struct kvm_io_device *dev,
			      gpa_t addr, const u32 *val)
{
	struct vgic_io_device *iodev = kvm_to_vgic_iodev(dev);
	const struct vgic_register_region *region;
	struct kvm_vcpu *r_vcpu;

	region = vgic_get_mmio_region(vcpu, iodev, addr, sizeof(u32));
	if (!region)
		return 0;

	r_vcpu = iodev->redist_vcpu ? iodev->redist_vcpu : vcpu;
	if (region->uaccess_write)
		return region->uaccess_write(r_vcpu, addr, sizeof(u32), *val);

	region->write(r_vcpu, addr, sizeof(u32), *val);
	return 0;
}