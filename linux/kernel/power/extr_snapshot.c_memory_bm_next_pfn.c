#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long node_pfn; int node_bit; TYPE_2__* zone; TYPE_1__* node; } ;
struct memory_bitmap {TYPE_3__ cur; } ;
struct TYPE_5__ {unsigned long end_pfn; int start_pfn; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_BITS_PER_BLOCK ; 
 unsigned long BM_END_OF_MAP ; 
 int find_next_bit (int /*<<< orphan*/ ,unsigned long,int) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ rtree_next_node (struct memory_bitmap*) ; 

__attribute__((used)) static unsigned long memory_bm_next_pfn(struct memory_bitmap *bm)
{
	unsigned long bits, pfn, pages;
	int bit;

	do {
		pages	  = bm->cur.zone->end_pfn - bm->cur.zone->start_pfn;
		bits      = min(pages - bm->cur.node_pfn, BM_BITS_PER_BLOCK);
		bit	  = find_next_bit(bm->cur.node->data, bits,
					  bm->cur.node_bit);
		if (bit < bits) {
			pfn = bm->cur.zone->start_pfn + bm->cur.node_pfn + bit;
			bm->cur.node_bit = bit + 1;
			return pfn;
		}
	} while (rtree_next_node(bm));

	return BM_END_OF_MAP;
}