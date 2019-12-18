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
typedef  int /*<<< orphan*/  pud_t ;
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_s2pud_readonly (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_set_s2pud_readonly (int /*<<< orphan*/ *) ; 
 scalar_t__ stage2_pud_addr_end (struct kvm*,scalar_t__,scalar_t__) ; 
 scalar_t__ stage2_pud_huge (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_pud_none (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stage2_pud_offset (struct kvm*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stage2_wp_pmds (struct kvm*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void  stage2_wp_puds(struct kvm *kvm, pgd_t *pgd,
			    phys_addr_t addr, phys_addr_t end)
{
	pud_t *pud;
	phys_addr_t next;

	pud = stage2_pud_offset(kvm, pgd, addr);
	do {
		next = stage2_pud_addr_end(kvm, addr, end);
		if (!stage2_pud_none(kvm, *pud)) {
			if (stage2_pud_huge(kvm, *pud)) {
				if (!kvm_s2pud_readonly(pud))
					kvm_set_s2pud_readonly(pud);
			} else {
				stage2_wp_pmds(kvm, pud, addr, next);
			}
		}
	} while (pud++, addr = next, addr != end);
}