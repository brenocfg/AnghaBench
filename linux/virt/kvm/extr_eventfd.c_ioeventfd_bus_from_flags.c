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
typedef  enum kvm_bus { ____Placeholder_kvm_bus } kvm_bus ;
typedef  int __u32 ;

/* Variables and functions */
 int KVM_IOEVENTFD_FLAG_PIO ; 
 int KVM_IOEVENTFD_FLAG_VIRTIO_CCW_NOTIFY ; 
 int KVM_MMIO_BUS ; 
 int KVM_PIO_BUS ; 
 int KVM_VIRTIO_CCW_NOTIFY_BUS ; 

__attribute__((used)) static enum kvm_bus ioeventfd_bus_from_flags(__u32 flags)
{
	if (flags & KVM_IOEVENTFD_FLAG_PIO)
		return KVM_PIO_BUS;
	if (flags & KVM_IOEVENTFD_FLAG_VIRTIO_CCW_NOTIFY)
		return KVM_VIRTIO_CCW_NOTIFY_BUS;
	return KVM_MMIO_BUS;
}