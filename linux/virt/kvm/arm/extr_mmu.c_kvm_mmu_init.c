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
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int ALIGN_DOWN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_MASK ; 
 unsigned long PAGE_OFFSET ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_page (int) ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 scalar_t__ __hyp_idmap_text_end ; 
 scalar_t__ __hyp_idmap_text_start ; 
 scalar_t__ __kvm_cpu_uses_extended_idmap () ; 
 int /*<<< orphan*/  __kvm_extend_hypmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __kvm_hyp_init ; 
 int /*<<< orphan*/ * boot_hyp_pgd ; 
 int /*<<< orphan*/  free_hyp_pgds () ; 
 scalar_t__ high_memory ; 
 int hyp_idmap_end ; 
 int hyp_idmap_start ; 
 void* hyp_idmap_vector ; 
 int /*<<< orphan*/ * hyp_pgd ; 
 int /*<<< orphan*/  hyp_pgd_order ; 
 int io_map_base ; 
 int kern_hyp_va (unsigned long) ; 
 int /*<<< orphan*/  kvm_debug (char*,int,...) ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 int kvm_map_idmap_text (int /*<<< orphan*/ *) ; 
 void* kvm_virt_to_phys (scalar_t__) ; 
 int /*<<< orphan*/ * merged_hyp_pgd ; 

int kvm_mmu_init(void)
{
	int err;

	hyp_idmap_start = kvm_virt_to_phys(__hyp_idmap_text_start);
	hyp_idmap_start = ALIGN_DOWN(hyp_idmap_start, PAGE_SIZE);
	hyp_idmap_end = kvm_virt_to_phys(__hyp_idmap_text_end);
	hyp_idmap_end = ALIGN(hyp_idmap_end, PAGE_SIZE);
	hyp_idmap_vector = kvm_virt_to_phys(__kvm_hyp_init);

	/*
	 * We rely on the linker script to ensure at build time that the HYP
	 * init code does not cross a page boundary.
	 */
	BUG_ON((hyp_idmap_start ^ (hyp_idmap_end - 1)) & PAGE_MASK);

	kvm_debug("IDMAP page: %lx\n", hyp_idmap_start);
	kvm_debug("HYP VA range: %lx:%lx\n",
		  kern_hyp_va(PAGE_OFFSET),
		  kern_hyp_va((unsigned long)high_memory - 1));

	if (hyp_idmap_start >= kern_hyp_va(PAGE_OFFSET) &&
	    hyp_idmap_start <  kern_hyp_va((unsigned long)high_memory - 1) &&
	    hyp_idmap_start != (unsigned long)__hyp_idmap_text_start) {
		/*
		 * The idmap page is intersecting with the VA space,
		 * it is not safe to continue further.
		 */
		kvm_err("IDMAP intersecting with HYP VA, unable to continue\n");
		err = -EINVAL;
		goto out;
	}

	hyp_pgd = (pgd_t *)__get_free_pages(GFP_KERNEL | __GFP_ZERO, hyp_pgd_order);
	if (!hyp_pgd) {
		kvm_err("Hyp mode PGD not allocated\n");
		err = -ENOMEM;
		goto out;
	}

	if (__kvm_cpu_uses_extended_idmap()) {
		boot_hyp_pgd = (pgd_t *)__get_free_pages(GFP_KERNEL | __GFP_ZERO,
							 hyp_pgd_order);
		if (!boot_hyp_pgd) {
			kvm_err("Hyp boot PGD not allocated\n");
			err = -ENOMEM;
			goto out;
		}

		err = kvm_map_idmap_text(boot_hyp_pgd);
		if (err)
			goto out;

		merged_hyp_pgd = (pgd_t *)__get_free_page(GFP_KERNEL | __GFP_ZERO);
		if (!merged_hyp_pgd) {
			kvm_err("Failed to allocate extra HYP pgd\n");
			goto out;
		}
		__kvm_extend_hypmap(boot_hyp_pgd, hyp_pgd, merged_hyp_pgd,
				    hyp_idmap_start);
	} else {
		err = kvm_map_idmap_text(hyp_pgd);
		if (err)
			goto out;
	}

	io_map_base = hyp_idmap_start;
	return 0;
out:
	free_hyp_pgds();
	return err;
}