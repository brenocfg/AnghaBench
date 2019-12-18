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
struct kvm_memslots {int /*<<< orphan*/  generation; } ;
struct gfn_to_hva_cache {unsigned long gpa; unsigned long len; int hva; int /*<<< orphan*/ * memslot; int /*<<< orphan*/  generation; } ;
typedef  unsigned long gpa_t ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int KVM_HVA_ERR_BAD ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/ * __gfn_to_memslot (struct kvm_memslots*,scalar_t__) ; 
 int gfn_to_hva_many (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ kvm_is_error_hva (int) ; 
 int offset_in_page (unsigned long) ; 

__attribute__((used)) static int __kvm_gfn_to_hva_cache_init(struct kvm_memslots *slots,
				       struct gfn_to_hva_cache *ghc,
				       gpa_t gpa, unsigned long len)
{
	int offset = offset_in_page(gpa);
	gfn_t start_gfn = gpa >> PAGE_SHIFT;
	gfn_t end_gfn = (gpa + len - 1) >> PAGE_SHIFT;
	gfn_t nr_pages_needed = end_gfn - start_gfn + 1;
	gfn_t nr_pages_avail;
	int r = start_gfn <= end_gfn ? 0 : -EINVAL;

	ghc->gpa = gpa;
	ghc->generation = slots->generation;
	ghc->len = len;
	ghc->hva = KVM_HVA_ERR_BAD;

	/*
	 * If the requested region crosses two memslots, we still
	 * verify that the entire region is valid here.
	 */
	while (!r && start_gfn <= end_gfn) {
		ghc->memslot = __gfn_to_memslot(slots, start_gfn);
		ghc->hva = gfn_to_hva_many(ghc->memslot, start_gfn,
					   &nr_pages_avail);
		if (kvm_is_error_hva(ghc->hva))
			r = -EFAULT;
		start_gfn += nr_pages_avail;
	}

	/* Use the slow path for cross page reads and writes. */
	if (!r && nr_pages_needed == 1)
		ghc->hva += offset;
	else
		ghc->memslot = NULL;

	return r;
}