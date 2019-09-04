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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcpu_get_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 smccc_get_function(struct kvm_vcpu *vcpu)
{
	return vcpu_get_reg(vcpu, 0);
}