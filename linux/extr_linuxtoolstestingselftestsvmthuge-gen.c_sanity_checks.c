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
 unsigned long NUM_PAGES ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 unsigned long getpagesize () ; 
 int num_page_sizes ; 
 unsigned long* page_sizes ; 
 int /*<<< orphan*/  printf (char*,unsigned long,...) ; 
 unsigned long read_free (unsigned long) ; 
 unsigned long read_sysfs (int /*<<< orphan*/ ,char*) ; 

void sanity_checks(void)
{
	int i;
	unsigned long largest = getpagesize();

	for (i = 0; i < num_page_sizes; i++) {
		if (page_sizes[i] > largest)
			largest = page_sizes[i];

		if (read_free(page_sizes[i]) < NUM_PAGES) {
			printf("Not enough huge pages for page size %lu MB, need %u\n",
				page_sizes[i] >> 20,
				NUM_PAGES);
			exit(0);
		}
	}

	if (read_sysfs(0, "/proc/sys/kernel/shmmax") < NUM_PAGES * largest) {
		printf("Please do echo %lu > /proc/sys/kernel/shmmax", largest * NUM_PAGES);
		exit(0);
	}

#if defined(__x86_64__)
	if (largest != 1U<<30) {
		printf("No GB pages available on x86-64\n"
		       "Please boot with hugepagesz=1G hugepages=%d\n", NUM_PAGES);
		exit(0);
	}
#endif
}