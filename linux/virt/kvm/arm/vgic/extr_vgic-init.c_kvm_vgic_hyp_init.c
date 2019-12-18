#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gic_kvm_info {int type; scalar_t__ maint_irq; } ;
struct TYPE_2__ {scalar_t__ maint_irq; int /*<<< orphan*/  gicv3_cpuif; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_KVM_ARM_VGIC_INIT_STARTING ; 
 int ENODEV ; 
 int ENXIO ; 
#define  GIC_V2 129 
#define  GIC_V3 128 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu_irq (scalar_t__,int /*<<< orphan*/ ) ; 
 struct gic_kvm_info* gic_get_kvm_info () ; 
 int /*<<< orphan*/  kvm_err (char*,...) ; 
 int /*<<< orphan*/  kvm_get_running_vcpus () ; 
 int /*<<< orphan*/  kvm_info (char*,...) ; 
 TYPE_1__ kvm_vgic_global_state ; 
 int request_percpu_irq (scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_branch_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_init_cpu_dying ; 
 int /*<<< orphan*/  vgic_init_cpu_starting ; 
 int /*<<< orphan*/  vgic_maintenance_handler ; 
 int vgic_v2_probe (struct gic_kvm_info const*) ; 
 int vgic_v3_probe (struct gic_kvm_info const*) ; 

int kvm_vgic_hyp_init(void)
{
	const struct gic_kvm_info *gic_kvm_info;
	int ret;

	gic_kvm_info = gic_get_kvm_info();
	if (!gic_kvm_info)
		return -ENODEV;

	if (!gic_kvm_info->maint_irq) {
		kvm_err("No vgic maintenance irq\n");
		return -ENXIO;
	}

	switch (gic_kvm_info->type) {
	case GIC_V2:
		ret = vgic_v2_probe(gic_kvm_info);
		break;
	case GIC_V3:
		ret = vgic_v3_probe(gic_kvm_info);
		if (!ret) {
			static_branch_enable(&kvm_vgic_global_state.gicv3_cpuif);
			kvm_info("GIC system register CPU interface enabled\n");
		}
		break;
	default:
		ret = -ENODEV;
	}

	if (ret)
		return ret;

	kvm_vgic_global_state.maint_irq = gic_kvm_info->maint_irq;
	ret = request_percpu_irq(kvm_vgic_global_state.maint_irq,
				 vgic_maintenance_handler,
				 "vgic", kvm_get_running_vcpus());
	if (ret) {
		kvm_err("Cannot register interrupt %d\n",
			kvm_vgic_global_state.maint_irq);
		return ret;
	}

	ret = cpuhp_setup_state(CPUHP_AP_KVM_ARM_VGIC_INIT_STARTING,
				"kvm/arm/vgic:starting",
				vgic_init_cpu_starting, vgic_init_cpu_dying);
	if (ret) {
		kvm_err("Cannot register vgic CPU notifier\n");
		goto out_free_irq;
	}

	kvm_info("vgic interrupt IRQ%d\n", kvm_vgic_global_state.maint_irq);
	return 0;

out_free_irq:
	free_percpu_irq(kvm_vgic_global_state.maint_irq,
			kvm_get_running_vcpus());
	return ret;
}