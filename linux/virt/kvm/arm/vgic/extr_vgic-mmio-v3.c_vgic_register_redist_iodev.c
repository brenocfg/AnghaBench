#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vgic_redist_region {int free_index; scalar_t__ base; } ;
struct vgic_io_device {int /*<<< orphan*/  dev; struct kvm_vcpu* redist_vcpu; int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  regions; int /*<<< orphan*/  iodev_type; scalar_t__ base_addr; } ;
struct vgic_dist {int /*<<< orphan*/  rd_regions; } ;
struct vgic_cpu {struct vgic_redist_region* rdreg; struct vgic_io_device rd_iodev; } ;
struct TYPE_4__ {struct vgic_cpu vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; struct kvm* kvm; } ;
struct TYPE_3__ {struct vgic_dist vgic; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_1__ arch; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IODEV_REDIST ; 
 int /*<<< orphan*/  IS_VGIC_ADDR_UNDEF (scalar_t__) ; 
 int /*<<< orphan*/  KVM_MMIO_BUS ; 
 int KVM_VGIC_V3_REDIST_SIZE ; 
 int SZ_64K ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_io_gic_ops ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_v3_check_base (struct kvm*) ; 
 int /*<<< orphan*/  vgic_v3_rd_registers ; 
 struct vgic_redist_region* vgic_v3_rdist_free_slot (int /*<<< orphan*/ *) ; 

int vgic_register_redist_iodev(struct kvm_vcpu *vcpu)
{
	struct kvm *kvm = vcpu->kvm;
	struct vgic_dist *vgic = &kvm->arch.vgic;
	struct vgic_cpu *vgic_cpu = &vcpu->arch.vgic_cpu;
	struct vgic_io_device *rd_dev = &vcpu->arch.vgic_cpu.rd_iodev;
	struct vgic_redist_region *rdreg;
	gpa_t rd_base;
	int ret;

	if (!IS_VGIC_ADDR_UNDEF(vgic_cpu->rd_iodev.base_addr))
		return 0;

	/*
	 * We may be creating VCPUs before having set the base address for the
	 * redistributor region, in which case we will come back to this
	 * function for all VCPUs when the base address is set.  Just return
	 * without doing any work for now.
	 */
	rdreg = vgic_v3_rdist_free_slot(&vgic->rd_regions);
	if (!rdreg)
		return 0;

	if (!vgic_v3_check_base(kvm))
		return -EINVAL;

	vgic_cpu->rdreg = rdreg;

	rd_base = rdreg->base + rdreg->free_index * KVM_VGIC_V3_REDIST_SIZE;

	kvm_iodevice_init(&rd_dev->dev, &kvm_io_gic_ops);
	rd_dev->base_addr = rd_base;
	rd_dev->iodev_type = IODEV_REDIST;
	rd_dev->regions = vgic_v3_rd_registers;
	rd_dev->nr_regions = ARRAY_SIZE(vgic_v3_rd_registers);
	rd_dev->redist_vcpu = vcpu;

	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_register_dev(kvm, KVM_MMIO_BUS, rd_base,
				      2 * SZ_64K, &rd_dev->dev);
	mutex_unlock(&kvm->slots_lock);

	if (ret)
		return ret;

	rdreg->free_index++;
	return 0;
}