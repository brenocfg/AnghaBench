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
typedef  scalar_t__ u32 ;
struct avtab_node {int dummy; } ;
struct avtab {scalar_t__ nslot; scalar_t__ mask; scalar_t__ nel; int /*<<< orphan*/  htable; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 scalar_t__ MAX_AVTAB_HASH_BUCKETS ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  flex_array_alloc (int,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 

int avtab_alloc(struct avtab *h, u32 nrules)
{
	u32 mask = 0;
	u32 shift = 0;
	u32 work = nrules;
	u32 nslot = 0;

	if (nrules == 0)
		goto avtab_alloc_out;

	while (work) {
		work  = work >> 1;
		shift++;
	}
	if (shift > 2)
		shift = shift - 2;
	nslot = 1 << shift;
	if (nslot > MAX_AVTAB_HASH_BUCKETS)
		nslot = MAX_AVTAB_HASH_BUCKETS;
	mask = nslot - 1;

	h->htable = flex_array_alloc(sizeof(struct avtab_node *), nslot,
				     GFP_KERNEL | __GFP_ZERO);
	if (!h->htable)
		return -ENOMEM;

 avtab_alloc_out:
	h->nel = 0;
	h->nslot = nslot;
	h->mask = mask;
	pr_debug("SELinux: %d avtab hash slots, %d rules.\n",
	       h->nslot, nrules);
	return 0;
}