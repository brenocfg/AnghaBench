#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {scalar_t__ pgoff; struct page* page; TYPE_4__* vma; } ;
struct page {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pio_data; } ;
struct kvm_vcpu {TYPE_2__* kvm; TYPE_1__ arch; int /*<<< orphan*/  run; } ;
struct TYPE_8__ {TYPE_3__* vm_file; } ;
struct TYPE_7__ {struct kvm_vcpu* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  coalesced_mmio_ring; } ;

/* Variables and functions */
 scalar_t__ KVM_COALESCED_MMIO_PAGE_OFFSET ; 
 scalar_t__ KVM_PIO_PAGE_OFFSET ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_fault (struct kvm_vcpu*,struct vm_fault*) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_fault_t kvm_vcpu_fault(struct vm_fault *vmf)
{
	struct kvm_vcpu *vcpu = vmf->vma->vm_file->private_data;
	struct page *page;

	if (vmf->pgoff == 0)
		page = virt_to_page(vcpu->run);
#ifdef CONFIG_X86
	else if (vmf->pgoff == KVM_PIO_PAGE_OFFSET)
		page = virt_to_page(vcpu->arch.pio_data);
#endif
#ifdef CONFIG_KVM_MMIO
	else if (vmf->pgoff == KVM_COALESCED_MMIO_PAGE_OFFSET)
		page = virt_to_page(vcpu->kvm->coalesced_mmio_ring);
#endif
	else
		return kvm_arch_vcpu_fault(vcpu, vmf);
	get_page(page);
	vmf->page = page;
	return 0;
}