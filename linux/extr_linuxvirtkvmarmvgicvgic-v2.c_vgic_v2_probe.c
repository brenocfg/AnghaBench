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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;
struct gic_kvm_info {TYPE_1__ vctrl; TYPE_1__ vcpu; } ;
struct TYPE_4__ {int nr_lr; int can_emulate_gicv2; scalar_t__ vcpu_base_va; scalar_t__ vctrl_base; int /*<<< orphan*/  max_gic_vcpus; int /*<<< orphan*/  type; int /*<<< orphan*/  vcpu_base; int /*<<< orphan*/  vctrl_hyp; int /*<<< orphan*/  vcpu_hyp_va; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ GICH_VTR ; 
 int /*<<< orphan*/  KVM_DEV_TYPE_ARM_VGIC_V2 ; 
 int /*<<< orphan*/  PAGE_ALIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGIC_V2 ; 
 int /*<<< orphan*/  VGIC_V2_MAX_CPUS ; 
 int create_hyp_io_mappings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kvm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 int /*<<< orphan*/  kvm_info (char*) ; 
 int kvm_register_vgic_device (int /*<<< orphan*/ ) ; 
 TYPE_2__ kvm_vgic_global_state ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  static_branch_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_v2_cpuif_trap ; 

int vgic_v2_probe(const struct gic_kvm_info *info)
{
	int ret;
	u32 vtr;

	if (!info->vctrl.start) {
		kvm_err("GICH not present in the firmware table\n");
		return -ENXIO;
	}

	if (!PAGE_ALIGNED(info->vcpu.start) ||
	    !PAGE_ALIGNED(resource_size(&info->vcpu))) {
		kvm_info("GICV region size/alignment is unsafe, using trapping (reduced performance)\n");

		ret = create_hyp_io_mappings(info->vcpu.start,
					     resource_size(&info->vcpu),
					     &kvm_vgic_global_state.vcpu_base_va,
					     &kvm_vgic_global_state.vcpu_hyp_va);
		if (ret) {
			kvm_err("Cannot map GICV into hyp\n");
			goto out;
		}

		static_branch_enable(&vgic_v2_cpuif_trap);
	}

	ret = create_hyp_io_mappings(info->vctrl.start,
				     resource_size(&info->vctrl),
				     &kvm_vgic_global_state.vctrl_base,
				     &kvm_vgic_global_state.vctrl_hyp);
	if (ret) {
		kvm_err("Cannot map VCTRL into hyp\n");
		goto out;
	}

	vtr = readl_relaxed(kvm_vgic_global_state.vctrl_base + GICH_VTR);
	kvm_vgic_global_state.nr_lr = (vtr & 0x3f) + 1;

	ret = kvm_register_vgic_device(KVM_DEV_TYPE_ARM_VGIC_V2);
	if (ret) {
		kvm_err("Cannot register GICv2 KVM device\n");
		goto out;
	}

	kvm_vgic_global_state.can_emulate_gicv2 = true;
	kvm_vgic_global_state.vcpu_base = info->vcpu.start;
	kvm_vgic_global_state.type = VGIC_V2;
	kvm_vgic_global_state.max_gic_vcpus = VGIC_V2_MAX_CPUS;

	kvm_debug("vgic-v2@%llx\n", info->vctrl.start);

	return 0;
out:
	if (kvm_vgic_global_state.vctrl_base)
		iounmap(kvm_vgic_global_state.vctrl_base);
	if (kvm_vgic_global_state.vcpu_base_va)
		iounmap(kvm_vgic_global_state.vcpu_base_va);

	return ret;
}