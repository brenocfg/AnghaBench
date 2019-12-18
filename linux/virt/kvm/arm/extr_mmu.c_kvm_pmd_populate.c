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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mk_pmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void kvm_pmd_populate(pmd_t *pmdp, pte_t *ptep)
{
	kvm_set_pmd(pmdp, kvm_mk_pmd(ptep));
}