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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int create_hyp_pmd_mappings (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_err (char*) ; 
 int /*<<< orphan*/  kvm_pud_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_alloc_one (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pud_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_hyp_pud_mappings(pgd_t *pgd, unsigned long start,
				   unsigned long end, unsigned long pfn,
				   pgprot_t prot)
{
	pud_t *pud;
	pmd_t *pmd;
	unsigned long addr, next;
	int ret;

	addr = start;
	do {
		pud = pud_offset(pgd, addr);

		if (pud_none_or_clear_bad(pud)) {
			pmd = pmd_alloc_one(NULL, addr);
			if (!pmd) {
				kvm_err("Cannot allocate Hyp pmd\n");
				return -ENOMEM;
			}
			kvm_pud_populate(pud, pmd);
			get_page(virt_to_page(pud));
		}

		next = pud_addr_end(addr, end);
		ret = create_hyp_pmd_mappings(pud, addr, next, pfn, prot);
		if (ret)
			return ret;
		pfn += (next - addr) >> PAGE_SHIFT;
	} while (addr = next, addr != end);

	return 0;
}