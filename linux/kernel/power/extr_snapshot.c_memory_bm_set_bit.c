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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int memory_bm_find_bit (struct memory_bitmap*,unsigned long,void**,unsigned int*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,void*) ; 

__attribute__((used)) static void memory_bm_set_bit(struct memory_bitmap *bm, unsigned long pfn)
{
	void *addr;
	unsigned int bit;
	int error;

	error = memory_bm_find_bit(bm, pfn, &addr, &bit);
	BUG_ON(error);
	set_bit(bit, addr);
}