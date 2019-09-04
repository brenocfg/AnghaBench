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
struct vgic_dist {int ready; int /*<<< orphan*/  vgic_cpu_base; int /*<<< orphan*/  vgic_dist_base; } ;
struct TYPE_3__ {struct vgic_dist vgic; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  vcpu_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ IS_VGIC_ADDR_UNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_VGIC_V2_CPU_SIZE ; 
 int /*<<< orphan*/  VGIC_V2 ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 int kvm_phys_addr_ioremap (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ kvm_vgic_global_state ; 
 int /*<<< orphan*/  static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int vgic_init (struct kvm*) ; 
 scalar_t__ vgic_ready (struct kvm*) ; 
 int vgic_register_dist_iodev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_v2_check_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_v2_cpuif_trap ; 

int vgic_v2_map_resources(struct kvm *kvm)
{
	struct vgic_dist *dist = &kvm->arch.vgic;
	int ret = 0;

	if (vgic_ready(kvm))
		goto out;

	if (IS_VGIC_ADDR_UNDEF(dist->vgic_dist_base) ||
	    IS_VGIC_ADDR_UNDEF(dist->vgic_cpu_base)) {
		kvm_err("Need to set vgic cpu and dist addresses first\n");
		ret = -ENXIO;
		goto out;
	}

	if (!vgic_v2_check_base(dist->vgic_dist_base, dist->vgic_cpu_base)) {
		kvm_err("VGIC CPU and dist frames overlap\n");
		ret = -EINVAL;
		goto out;
	}

	/*
	 * Initialize the vgic if this hasn't already been done on demand by
	 * accessing the vgic state from userspace.
	 */
	ret = vgic_init(kvm);
	if (ret) {
		kvm_err("Unable to initialize VGIC dynamic data structures\n");
		goto out;
	}

	ret = vgic_register_dist_iodev(kvm, dist->vgic_dist_base, VGIC_V2);
	if (ret) {
		kvm_err("Unable to register VGIC MMIO regions\n");
		goto out;
	}

	if (!static_branch_unlikely(&vgic_v2_cpuif_trap)) {
		ret = kvm_phys_addr_ioremap(kvm, dist->vgic_cpu_base,
					    kvm_vgic_global_state.vcpu_base,
					    KVM_VGIC_V2_CPU_SIZE, true);
		if (ret) {
			kvm_err("Unable to remap VGIC CPU to VCPU\n");
			goto out;
		}
	}

	dist->ready = true;

out:
	return ret;
}