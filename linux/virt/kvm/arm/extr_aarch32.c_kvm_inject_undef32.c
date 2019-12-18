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
 int /*<<< orphan*/  PSR_AA32_MODE_UND ; 
 int /*<<< orphan*/  prepare_fault32 (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 

void kvm_inject_undef32(struct kvm_vcpu *vcpu)
{
	prepare_fault32(vcpu, PSR_AA32_MODE_UND, 4);
}