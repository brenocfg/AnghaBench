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
struct page {int dummy; } ;
struct kvm_memory_slot {int dummy; } ;
typedef  int gfn_t ;

/* Variables and functions */
 int __get_user_pages_fast (unsigned long,int,int,struct page**) ; 
 unsigned long gfn_to_hva_many (struct kvm_memory_slot*,int,int*) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 

int gfn_to_page_many_atomic(struct kvm_memory_slot *slot, gfn_t gfn,
			    struct page **pages, int nr_pages)
{
	unsigned long addr;
	gfn_t entry = 0;

	addr = gfn_to_hva_many(slot, gfn, &entry);
	if (kvm_is_error_hva(addr))
		return -1;

	if (entry < nr_pages)
		return 0;

	return __get_user_pages_fast(addr, nr_pages, 1, pages);
}