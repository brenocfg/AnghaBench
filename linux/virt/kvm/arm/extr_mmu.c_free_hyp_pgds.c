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
 scalar_t__ PAGE_OFFSET ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * boot_hyp_pgd ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ high_memory ; 
 scalar_t__ hyp_idmap_start ; 
 int /*<<< orphan*/ * hyp_pgd ; 
 int /*<<< orphan*/  hyp_pgd_order ; 
 scalar_t__ io_map_base ; 
 int /*<<< orphan*/  kern_hyp_va (scalar_t__) ; 
 int /*<<< orphan*/  kvm_hyp_pgd_mutex ; 
 int /*<<< orphan*/ * merged_hyp_pgd ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_hyp_idmap_range (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  unmap_hyp_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void free_hyp_pgds(void)
{
	pgd_t *id_pgd;

	mutex_lock(&kvm_hyp_pgd_mutex);

	id_pgd = boot_hyp_pgd ? boot_hyp_pgd : hyp_pgd;

	if (id_pgd) {
		/* In case we never called hyp_mmu_init() */
		if (!io_map_base)
			io_map_base = hyp_idmap_start;
		unmap_hyp_idmap_range(id_pgd, io_map_base,
				      hyp_idmap_start + PAGE_SIZE - io_map_base);
	}

	if (boot_hyp_pgd) {
		free_pages((unsigned long)boot_hyp_pgd, hyp_pgd_order);
		boot_hyp_pgd = NULL;
	}

	if (hyp_pgd) {
		unmap_hyp_range(hyp_pgd, kern_hyp_va(PAGE_OFFSET),
				(uintptr_t)high_memory - PAGE_OFFSET);

		free_pages((unsigned long)hyp_pgd, hyp_pgd_order);
		hyp_pgd = NULL;
	}
	if (merged_hyp_pgd) {
		clear_page(merged_hyp_pgd);
		free_page((unsigned long)merged_hyp_pgd);
		merged_hyp_pgd = NULL;
	}

	mutex_unlock(&kvm_hyp_pgd_mutex);
}