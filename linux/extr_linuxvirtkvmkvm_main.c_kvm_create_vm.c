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
struct kvm_memslots {int generation; } ;
struct kvm_io_bus {int dummy; } ;
struct kvm {int /*<<< orphan*/  users_count; int /*<<< orphan*/  srcu; int /*<<< orphan*/  irq_srcu; int /*<<< orphan*/  vm_list; int /*<<< orphan*/ * buses; int /*<<< orphan*/ * memslots; int /*<<< orphan*/  devices; int /*<<< orphan*/  slots_lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; int /*<<< orphan*/  mmu_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 struct kvm* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int KVM_ADDRESS_SPACE_NUM ; 
 scalar_t__ KVM_MEM_SLOTS_NUM ; 
 int KVM_NR_BUSES ; 
 scalar_t__ SHRT_MAX ; 
 int /*<<< orphan*/  __kvm_memslots (struct kvm*,int) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  hardware_disable_all () ; 
 int hardware_enable_all () ; 
 scalar_t__ init_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct kvm_memslots* kvm_alloc_memslots () ; 
 struct kvm* kvm_arch_alloc_vm () ; 
 int /*<<< orphan*/  kvm_arch_free_vm (struct kvm*) ; 
 int kvm_arch_init_vm (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  kvm_eventfd_init (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_memslots (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_get_bus (struct kvm*,int) ; 
 int kvm_init_mmu_notifier (struct kvm*) ; 
 int /*<<< orphan*/  kvm_lock ; 
 struct kvm_memslots* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_notifier_inc () ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct kvm_memslots*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_list ; 

__attribute__((used)) static struct kvm *kvm_create_vm(unsigned long type)
{
	int r, i;
	struct kvm *kvm = kvm_arch_alloc_vm();

	if (!kvm)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&kvm->mmu_lock);
	mmgrab(current->mm);
	kvm->mm = current->mm;
	kvm_eventfd_init(kvm);
	mutex_init(&kvm->lock);
	mutex_init(&kvm->irq_lock);
	mutex_init(&kvm->slots_lock);
	refcount_set(&kvm->users_count, 1);
	INIT_LIST_HEAD(&kvm->devices);

	r = kvm_arch_init_vm(kvm, type);
	if (r)
		goto out_err_no_disable;

	r = hardware_enable_all();
	if (r)
		goto out_err_no_disable;

#ifdef CONFIG_HAVE_KVM_IRQFD
	INIT_HLIST_HEAD(&kvm->irq_ack_notifier_list);
#endif

	BUILD_BUG_ON(KVM_MEM_SLOTS_NUM > SHRT_MAX);

	r = -ENOMEM;
	for (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++) {
		struct kvm_memslots *slots = kvm_alloc_memslots();
		if (!slots)
			goto out_err_no_srcu;
		/*
		 * Generations must be different for each address space.
		 * Init kvm generation close to the maximum to easily test the
		 * code of handling generation number wrap-around.
		 */
		slots->generation = i * 2 - 150;
		rcu_assign_pointer(kvm->memslots[i], slots);
	}

	if (init_srcu_struct(&kvm->srcu))
		goto out_err_no_srcu;
	if (init_srcu_struct(&kvm->irq_srcu))
		goto out_err_no_irq_srcu;
	for (i = 0; i < KVM_NR_BUSES; i++) {
		rcu_assign_pointer(kvm->buses[i],
			kzalloc(sizeof(struct kvm_io_bus), GFP_KERNEL));
		if (!kvm->buses[i])
			goto out_err;
	}

	r = kvm_init_mmu_notifier(kvm);
	if (r)
		goto out_err;

	spin_lock(&kvm_lock);
	list_add(&kvm->vm_list, &vm_list);
	spin_unlock(&kvm_lock);

	preempt_notifier_inc();

	return kvm;

out_err:
	cleanup_srcu_struct(&kvm->irq_srcu);
out_err_no_irq_srcu:
	cleanup_srcu_struct(&kvm->srcu);
out_err_no_srcu:
	hardware_disable_all();
out_err_no_disable:
	refcount_set(&kvm->users_count, 0);
	for (i = 0; i < KVM_NR_BUSES; i++)
		kfree(kvm_get_bus(kvm, i));
	for (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++)
		kvm_free_memslots(kvm, __kvm_memslots(kvm, i));
	kvm_arch_free_vm(kvm);
	mmdrop(current->mm);
	return ERR_PTR(r);
}