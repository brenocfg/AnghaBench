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
 int MAP_HUGETLB ; 
 int MAP_HUGE_SHIFT ; 
 int SHM_HUGETLB ; 
 int SHM_HUGE_SHIFT ; 
 unsigned int default_huge_page_size () ; 
 int /*<<< orphan*/  find_pagesizes () ; 
 unsigned int getpagesize () ; 
 int ilog2 (unsigned long) ; 
 int num_page_sizes ; 
 unsigned long* page_sizes ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  sanity_checks () ; 
 int /*<<< orphan*/  test_mmap (unsigned int,int) ; 
 int /*<<< orphan*/  test_shmget (unsigned int,int) ; 

int main(void)
{
	int i;
	unsigned default_hps = default_huge_page_size();

	find_pagesizes();

	sanity_checks();

	for (i = 0; i < num_page_sizes; i++) {
		unsigned long ps = page_sizes[i];
		int arg = ilog2(ps) << MAP_HUGE_SHIFT;
		printf("Testing %luMB mmap with shift %x\n", ps >> 20, arg);
		test_mmap(ps, MAP_HUGETLB | arg);
	}
	printf("Testing default huge mmap\n");
	test_mmap(default_hps, SHM_HUGETLB);

	puts("Testing non-huge shmget");
	test_shmget(getpagesize(), 0);

	for (i = 0; i < num_page_sizes; i++) {
		unsigned long ps = page_sizes[i];
		int arg = ilog2(ps) << SHM_HUGE_SHIFT;
		printf("Testing %luMB shmget with shift %x\n", ps >> 20, arg);
		test_shmget(ps, SHM_HUGETLB | arg);
	}
	puts("default huge shmget");
	test_shmget(default_hps, SHM_HUGETLB);

	return 0;
}