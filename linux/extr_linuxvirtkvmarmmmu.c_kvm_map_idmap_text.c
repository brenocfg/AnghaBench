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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_HYP_EXEC ; 
 int __create_hyp_mappings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kvm_idmap_ptrs_per_pgd () ; 
 int /*<<< orphan*/  __phys_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hyp_idmap_end ; 
 int /*<<< orphan*/  hyp_idmap_start ; 
 int /*<<< orphan*/  kvm_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_map_idmap_text(pgd_t *pgd)
{
	int err;

	/* Create the idmap in the boot page tables */
	err = 	__create_hyp_mappings(pgd, __kvm_idmap_ptrs_per_pgd(),
				      hyp_idmap_start, hyp_idmap_end,
				      __phys_to_pfn(hyp_idmap_start),
				      PAGE_HYP_EXEC);
	if (err)
		kvm_err("Failed to idmap %lx-%lx\n",
			hyp_idmap_start, hyp_idmap_end);

	return err;
}