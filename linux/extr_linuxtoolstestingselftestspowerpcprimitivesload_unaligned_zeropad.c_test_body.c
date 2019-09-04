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
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int MAP_ANONYMOUS ; 
 unsigned long* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int do_one_test (unsigned long*,unsigned long) ; 
 int getpagesize () ; 
 unsigned long* mem_region ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 unsigned long* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int page_size ; 
 int /*<<< orphan*/  setup_segv_handler () ; 

__attribute__((used)) static int test_body(void)
{
	unsigned long i;

	page_size = getpagesize();
	mem_region = mmap(NULL, page_size * 2, PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	FAIL_IF(mem_region == MAP_FAILED);

	for (i = 0; i < page_size; i++)
		mem_region[i] = i;

	memset(mem_region+page_size, 0, page_size);

	setup_segv_handler();

	for (i = 0; i < page_size; i++)
		FAIL_IF(do_one_test(mem_region+i, i));

	return 0;
}