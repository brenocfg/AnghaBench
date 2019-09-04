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

/* Variables and functions */
 int PAGE_SIZE ; 
 int PCPU_MIN_ALLOC_SIZE ; 

__attribute__((used)) static inline int pcpu_nr_pages_to_map_bits(int pages)
{
	return pages * PAGE_SIZE / PCPU_MIN_ALLOC_SIZE;
}