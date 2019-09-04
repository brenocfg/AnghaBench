#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * pgd; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  S2_PGD_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/ * alloc_pages_exact (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_err (char*) ; 

int kvm_alloc_stage2_pgd(struct kvm *kvm)
{
	pgd_t *pgd;

	if (kvm->arch.pgd != NULL) {
		kvm_err("kvm_arch already initialized?\n");
		return -EINVAL;
	}

	/* Allocate the HW PGD, making sure that each page gets its own refcount */
	pgd = alloc_pages_exact(S2_PGD_SIZE, GFP_KERNEL | __GFP_ZERO);
	if (!pgd)
		return -ENOMEM;

	kvm->arch.pgd = pgd;
	return 0;
}