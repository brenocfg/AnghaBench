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
struct kvm_ioeventfd {int flags; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int KVM_IOEVENTFD_FLAG_DEASSIGN ; 
 int kvm_assign_ioeventfd (struct kvm*,struct kvm_ioeventfd*) ; 
 int kvm_deassign_ioeventfd (struct kvm*,struct kvm_ioeventfd*) ; 

int
kvm_ioeventfd(struct kvm *kvm, struct kvm_ioeventfd *args)
{
	if (args->flags & KVM_IOEVENTFD_FLAG_DEASSIGN)
		return kvm_deassign_ioeventfd(kvm, args);

	return kvm_assign_ioeventfd(kvm, args);
}