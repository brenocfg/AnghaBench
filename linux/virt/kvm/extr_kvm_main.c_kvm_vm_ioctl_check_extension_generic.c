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
struct kvm {int dummy; } ;

/* Variables and functions */
 long KVM_ADDRESS_SPACE_NUM ; 
#define  KVM_CAP_CHECK_EXTENSION_VM 143 
#define  KVM_CAP_COALESCED_MMIO 142 
#define  KVM_CAP_COALESCED_PIO 141 
#define  KVM_CAP_DESTROY_MEMORY_REGION_WORKS 140 
#define  KVM_CAP_ENABLE_CAP_VM 139 
#define  KVM_CAP_INTERNAL_ERROR_DATA 138 
#define  KVM_CAP_IOEVENTFD_ANY_LENGTH 137 
#define  KVM_CAP_IRQFD 136 
#define  KVM_CAP_IRQFD_RESAMPLE 135 
#define  KVM_CAP_IRQ_ROUTING 134 
#define  KVM_CAP_JOIN_MEMORY_REGIONS_WORKS 133 
#define  KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 132 
#define  KVM_CAP_MULTI_ADDRESS_SPACE 131 
#define  KVM_CAP_NR_MEMSLOTS 130 
#define  KVM_CAP_SIGNAL_MSI 129 
#define  KVM_CAP_USER_MEMORY 128 
 long KVM_COALESCED_MMIO_PAGE_OFFSET ; 
 long KVM_MAX_IRQ_ROUTES ; 
 long KVM_USER_MEM_SLOTS ; 
 long kvm_vm_ioctl_check_extension (struct kvm*,long) ; 

__attribute__((used)) static long kvm_vm_ioctl_check_extension_generic(struct kvm *kvm, long arg)
{
	switch (arg) {
	case KVM_CAP_USER_MEMORY:
	case KVM_CAP_DESTROY_MEMORY_REGION_WORKS:
	case KVM_CAP_JOIN_MEMORY_REGIONS_WORKS:
	case KVM_CAP_INTERNAL_ERROR_DATA:
#ifdef CONFIG_HAVE_KVM_MSI
	case KVM_CAP_SIGNAL_MSI:
#endif
#ifdef CONFIG_HAVE_KVM_IRQFD
	case KVM_CAP_IRQFD:
	case KVM_CAP_IRQFD_RESAMPLE:
#endif
	case KVM_CAP_IOEVENTFD_ANY_LENGTH:
	case KVM_CAP_CHECK_EXTENSION_VM:
	case KVM_CAP_ENABLE_CAP_VM:
#ifdef CONFIG_KVM_GENERIC_DIRTYLOG_READ_PROTECT
	case KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2:
#endif
		return 1;
#ifdef CONFIG_KVM_MMIO
	case KVM_CAP_COALESCED_MMIO:
		return KVM_COALESCED_MMIO_PAGE_OFFSET;
	case KVM_CAP_COALESCED_PIO:
		return 1;
#endif
#ifdef CONFIG_HAVE_KVM_IRQ_ROUTING
	case KVM_CAP_IRQ_ROUTING:
		return KVM_MAX_IRQ_ROUTES;
#endif
#if KVM_ADDRESS_SPACE_NUM > 1
	case KVM_CAP_MULTI_ADDRESS_SPACE:
		return KVM_ADDRESS_SPACE_NUM;
#endif
	case KVM_CAP_NR_MEMSLOTS:
		return KVM_USER_MEM_SLOTS;
	default:
		break;
	}
	return kvm_vm_ioctl_check_extension(kvm, arg);
}