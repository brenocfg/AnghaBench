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
 int /*<<< orphan*/  KVM_DEV_TYPE_VFIO ; 
 int kvm_register_device_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vfio_ops ; 

int kvm_vfio_ops_init(void)
{
	return kvm_register_device_ops(&kvm_vfio_ops, KVM_DEV_TYPE_VFIO);
}