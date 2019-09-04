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
#define  KVM_CAP_CHECK_EXTENSION_VM 134 
#define  KVM_CAP_DESTROY_MEMORY_REGION_WORKS 133 
#define  KVM_CAP_INTERNAL_ERROR_DATA 132 
#define  KVM_CAP_IOEVENTFD_ANY_LENGTH 131 
#define  KVM_CAP_JOIN_MEMORY_REGIONS_WORKS 130 
#define  KVM_CAP_MAX_VCPU_ID 129 
#define  KVM_CAP_USER_MEMORY 128 
 long KVM_MAX_VCPU_ID ; 
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
		return 1;
#ifdef CONFIG_KVM_MMIO
	case KVM_CAP_COALESCED_MMIO:
		return KVM_COALESCED_MMIO_PAGE_OFFSET;
#endif
#ifdef CONFIG_HAVE_KVM_IRQ_ROUTING
	case KVM_CAP_IRQ_ROUTING:
		return KVM_MAX_IRQ_ROUTES;
#endif
#if KVM_ADDRESS_SPACE_NUM > 1
	case KVM_CAP_MULTI_ADDRESS_SPACE:
		return KVM_ADDRESS_SPACE_NUM;
#endif
	case KVM_CAP_MAX_VCPU_ID:
		return KVM_MAX_VCPU_ID;
	default:
		break;
	}
	return kvm_vm_ioctl_check_extension(kvm, arg);
}