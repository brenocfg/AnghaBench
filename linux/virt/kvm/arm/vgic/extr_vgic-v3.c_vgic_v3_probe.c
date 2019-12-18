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
struct TYPE_3__ {scalar_t__ start; } ;
struct gic_kvm_info {TYPE_1__ vcpu; scalar_t__ has_v4; } ;
struct TYPE_4__ {int nr_lr; int can_emulate_gicv2; int ich_vtr_el2; scalar_t__ vcpu_base; int /*<<< orphan*/  max_gic_vcpus; int /*<<< orphan*/  type; int /*<<< orphan*/ * vctrl_base; scalar_t__ has_gicv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_WORKAROUND_CAVIUM_30115 ; 
 int /*<<< orphan*/  KVM_DEV_TYPE_ARM_VGIC_V2 ; 
 int /*<<< orphan*/  KVM_DEV_TYPE_ARM_VGIC_V3 ; 
 int /*<<< orphan*/  PAGE_ALIGNED (scalar_t__) ; 
 int /*<<< orphan*/  VGIC_V3 ; 
 int /*<<< orphan*/  VGIC_V3_MAX_CPUS ; 
 int /*<<< orphan*/  __vgic_v3_get_ich_vtr_el2 ; 
 scalar_t__ common_trap ; 
 scalar_t__ cpus_have_const_cap (int /*<<< orphan*/ ) ; 
 scalar_t__ gicv4_enable ; 
 int group0_trap ; 
 int group1_trap ; 
 int kvm_call_hyp_ret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 int /*<<< orphan*/  kvm_info (char*,...) ; 
 int kvm_register_vgic_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_unregister_device_ops (int /*<<< orphan*/ ) ; 
 TYPE_2__ kvm_vgic_global_state ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long long) ; 
 int /*<<< orphan*/  static_branch_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_v3_cpuif_trap ; 

int vgic_v3_probe(const struct gic_kvm_info *info)
{
	u32 ich_vtr_el2 = kvm_call_hyp_ret(__vgic_v3_get_ich_vtr_el2);
	int ret;

	/*
	 * The ListRegs field is 5 bits, but there is a architectural
	 * maximum of 16 list registers. Just ignore bit 4...
	 */
	kvm_vgic_global_state.nr_lr = (ich_vtr_el2 & 0xf) + 1;
	kvm_vgic_global_state.can_emulate_gicv2 = false;
	kvm_vgic_global_state.ich_vtr_el2 = ich_vtr_el2;

	/* GICv4 support? */
	if (info->has_v4) {
		kvm_vgic_global_state.has_gicv4 = gicv4_enable;
		kvm_info("GICv4 support %sabled\n",
			 gicv4_enable ? "en" : "dis");
	}

	if (!info->vcpu.start) {
		kvm_info("GICv3: no GICV resource entry\n");
		kvm_vgic_global_state.vcpu_base = 0;
	} else if (!PAGE_ALIGNED(info->vcpu.start)) {
		pr_warn("GICV physical address 0x%llx not page aligned\n",
			(unsigned long long)info->vcpu.start);
		kvm_vgic_global_state.vcpu_base = 0;
	} else {
		kvm_vgic_global_state.vcpu_base = info->vcpu.start;
		kvm_vgic_global_state.can_emulate_gicv2 = true;
		ret = kvm_register_vgic_device(KVM_DEV_TYPE_ARM_VGIC_V2);
		if (ret) {
			kvm_err("Cannot register GICv2 KVM device.\n");
			return ret;
		}
		kvm_info("vgic-v2@%llx\n", info->vcpu.start);
	}
	ret = kvm_register_vgic_device(KVM_DEV_TYPE_ARM_VGIC_V3);
	if (ret) {
		kvm_err("Cannot register GICv3 KVM device.\n");
		kvm_unregister_device_ops(KVM_DEV_TYPE_ARM_VGIC_V2);
		return ret;
	}

	if (kvm_vgic_global_state.vcpu_base == 0)
		kvm_info("disabling GICv2 emulation\n");

#ifdef CONFIG_ARM64
	if (cpus_have_const_cap(ARM64_WORKAROUND_CAVIUM_30115)) {
		group0_trap = true;
		group1_trap = true;
	}
#endif

	if (group0_trap || group1_trap || common_trap) {
		kvm_info("GICv3 sysreg trapping enabled ([%s%s%s], reduced performance)\n",
			 group0_trap ? "G0" : "",
			 group1_trap ? "G1" : "",
			 common_trap ? "C"  : "");
		static_branch_enable(&vgic_v3_cpuif_trap);
	}

	kvm_vgic_global_state.vctrl_base = NULL;
	kvm_vgic_global_state.type = VGIC_V3;
	kvm_vgic_global_state.max_gic_vcpus = VGIC_V3_MAX_CPUS;

	return 0;
}