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

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_KVM_STARTING ; 
 int /*<<< orphan*/  cpuhp_remove_state_nocalls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_hardware_enabled ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardware_disable_nolock ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arch_exit () ; 
 int /*<<< orphan*/  kvm_arch_hardware_unsetup () ; 
 int /*<<< orphan*/  kvm_async_pf_deinit () ; 
 int /*<<< orphan*/  kvm_debugfs_dir ; 
 int /*<<< orphan*/  kvm_dev ; 
 int /*<<< orphan*/  kvm_irqfd_exit () ; 
 int /*<<< orphan*/  kvm_reboot_notifier ; 
 int /*<<< orphan*/  kvm_syscore_ops ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  kvm_vfio_ops_exit () ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_syscore_ops (int /*<<< orphan*/ *) ; 

void kvm_exit(void)
{
	debugfs_remove_recursive(kvm_debugfs_dir);
	misc_deregister(&kvm_dev);
	kmem_cache_destroy(kvm_vcpu_cache);
	kvm_async_pf_deinit();
	unregister_syscore_ops(&kvm_syscore_ops);
	unregister_reboot_notifier(&kvm_reboot_notifier);
	cpuhp_remove_state_nocalls(CPUHP_AP_KVM_STARTING);
	on_each_cpu(hardware_disable_nolock, NULL, 1);
	kvm_arch_hardware_unsetup();
	kvm_arch_exit();
	kvm_irqfd_exit();
	free_cpumask_var(cpus_hardware_enabled);
	kvm_vfio_ops_exit();
}