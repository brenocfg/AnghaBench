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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned long vcpu_get_reg (struct kvm_vcpu*,int) ; 

__attribute__((used)) static unsigned long smccc_get_arg3(struct kvm_vcpu *vcpu)
{
	return vcpu_get_reg(vcpu, 3);
}