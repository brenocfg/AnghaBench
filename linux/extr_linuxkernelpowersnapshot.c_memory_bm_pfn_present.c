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
struct memory_bitmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memory_bm_find_bit (struct memory_bitmap*,unsigned long,void**,unsigned int*) ; 

__attribute__((used)) static bool memory_bm_pfn_present(struct memory_bitmap *bm, unsigned long pfn)
{
	void *addr;
	unsigned int bit;

	return !memory_bm_find_bit(bm, pfn, &addr, &bit);
}