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
struct request_queue {int dummy; } ;
struct bio_vec {unsigned long bv_offset; unsigned long bv_len; int /*<<< orphan*/  bv_page; } ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 unsigned long page_to_phys (int /*<<< orphan*/ ) ; 
 unsigned long queue_segment_boundary (struct request_queue*) ; 
 int /*<<< orphan*/  xen_biovec_phys_mergeable (struct bio_vec*,int /*<<< orphan*/ ) ; 
 scalar_t__ xen_domain () ; 

__attribute__((used)) static inline bool biovec_phys_mergeable(struct request_queue *q,
		struct bio_vec *vec1, struct bio_vec *vec2)
{
	unsigned long mask = queue_segment_boundary(q);
	phys_addr_t addr1 = page_to_phys(vec1->bv_page) + vec1->bv_offset;
	phys_addr_t addr2 = page_to_phys(vec2->bv_page) + vec2->bv_offset;

	if (addr1 + vec1->bv_len != addr2)
		return false;
	if (xen_domain() && !xen_biovec_phys_mergeable(vec1, vec2->bv_page))
		return false;
	if ((addr1 | mask) != ((addr2 + vec2->bv_len - 1) | mask))
		return false;
	return true;
}