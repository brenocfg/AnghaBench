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
typedef  size_t u32 ;
struct kvm_device_ops {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct kvm_device_ops**) ; 
 int EEXIST ; 
 int ENOSPC ; 
 struct kvm_device_ops** kvm_device_ops_table ; 

int kvm_register_device_ops(struct kvm_device_ops *ops, u32 type)
{
	if (type >= ARRAY_SIZE(kvm_device_ops_table))
		return -ENOSPC;

	if (kvm_device_ops_table[type] != NULL)
		return -EEXIST;

	kvm_device_ops_table[type] = ops;
	return 0;
}