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
struct z3fold_header {unsigned long last_chunks; } ;
struct z3fold_buddy_slots {unsigned long* slot; } ;
typedef  enum buddy { ____Placeholder_buddy } buddy ;

/* Variables and functions */
 unsigned long BUDDY_SHIFT ; 
 int HEADLESS ; 
 int LAST ; 
 int PAGE_HEADLESS ; 
 int __idx (struct z3fold_header*,int) ; 

__attribute__((used)) static unsigned long __encode_handle(struct z3fold_header *zhdr,
				struct z3fold_buddy_slots *slots,
				enum buddy bud)
{
	unsigned long h = (unsigned long)zhdr;
	int idx = 0;

	/*
	 * For a headless page, its handle is its pointer with the extra
	 * PAGE_HEADLESS bit set
	 */
	if (bud == HEADLESS)
		return h | (1 << PAGE_HEADLESS);

	/* otherwise, return pointer to encoded handle */
	idx = __idx(zhdr, bud);
	h += idx;
	if (bud == LAST)
		h |= (zhdr->last_chunks << BUDDY_SHIFT);

	slots->slot[idx] = h;
	return (unsigned long)&slots->slot[idx];
}