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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_SYNC (int) ; 
 scalar_t__ TEST_MEM_OFFSET ; 
 int volatile TEST_MEM_PAGES ; 
 int TEST_PAGES_PER_LOOP ; 
 int guest_iteration ; 
 int volatile guest_page_size ; 
 int* guest_random_array ; 

void guest_code(void)
{
	int i = 0;
	uint64_t volatile *array = guest_random_array;
	uint64_t volatile *guest_addr;

	while (true) {
		for (i = 0; i < TEST_PAGES_PER_LOOP; i++) {
			/*
			 * Write to the first 8 bytes of a random page
			 * on the testing memory region.
			 */
			guest_addr = (uint64_t *)
			    (TEST_MEM_OFFSET +
			     (array[i] % TEST_MEM_PAGES) * guest_page_size);
			*guest_addr = guest_iteration;
		}
		/* Tell the host that we need more random numbers */
		GUEST_SYNC(1);
	}
}