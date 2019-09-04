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
struct mm_struct {int dummy; } ;
struct kvm_io_bus {int dummy; } ;
struct kvm {int /*<<< orphan*/  srcu; int /*<<< orphan*/  irq_srcu; int /*<<< orphan*/ ** buses; int /*<<< orphan*/  vm_list; struct mm_struct* mm; } ;

/* Variables and functions */
 int KVM_ADDRESS_SPACE_NUM ; 
 int /*<<< orphan*/  KVM_EVENT_DESTROY_VM ; 
 int KVM_NR_BUSES ; 
 int /*<<< orphan*/  __kvm_memslots (struct kvm*,int) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hardware_disable_all () ; 
 int /*<<< orphan*/  kvm_arch_destroy_vm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_arch_flush_shadow_all (struct kvm*) ; 
 int /*<<< orphan*/  kvm_arch_free_vm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_arch_sync_events (struct kvm*) ; 
 int /*<<< orphan*/  kvm_coalesced_mmio_free (struct kvm*) ; 
 int /*<<< orphan*/  kvm_destroy_devices (struct kvm*) ; 
 int /*<<< orphan*/  kvm_destroy_vm_debugfs (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_irq_routing (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_memslots (struct kvm*,int /*<<< orphan*/ ) ; 
 struct kvm_io_bus* kvm_get_bus (struct kvm*,int) ; 
 int /*<<< orphan*/  kvm_io_bus_destroy (struct kvm_io_bus*) ; 
 int /*<<< orphan*/  kvm_lock ; 
 int /*<<< orphan*/  kvm_uevent_notify_change (int /*<<< orphan*/ ,struct kvm*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  preempt_notifier_dec () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_destroy_vm(struct kvm *kvm)
{
	int i;
	struct mm_struct *mm = kvm->mm;

	kvm_uevent_notify_change(KVM_EVENT_DESTROY_VM, kvm);
	kvm_destroy_vm_debugfs(kvm);
	kvm_arch_sync_events(kvm);
	spin_lock(&kvm_lock);
	list_del(&kvm->vm_list);
	spin_unlock(&kvm_lock);
	kvm_free_irq_routing(kvm);
	for (i = 0; i < KVM_NR_BUSES; i++) {
		struct kvm_io_bus *bus = kvm_get_bus(kvm, i);

		if (bus)
			kvm_io_bus_destroy(bus);
		kvm->buses[i] = NULL;
	}
	kvm_coalesced_mmio_free(kvm);
#if defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
	mmu_notifier_unregister(&kvm->mmu_notifier, kvm->mm);
#else
	kvm_arch_flush_shadow_all(kvm);
#endif
	kvm_arch_destroy_vm(kvm);
	kvm_destroy_devices(kvm);
	for (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++)
		kvm_free_memslots(kvm, __kvm_memslots(kvm, i));
	cleanup_srcu_struct(&kvm->irq_srcu);
	cleanup_srcu_struct(&kvm->srcu);
	kvm_arch_free_vm(kvm);
	preempt_notifier_dec();
	hardware_disable_all();
	mmdrop(mm);
}