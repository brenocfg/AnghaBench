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
 char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  PPC_FEATURE_ARCH_2_06 ; 
 int PROT_READ ; 
 int PROT_SAO ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SIZE ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  have_hwcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 char* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

int test_prot_sao(void)
{
	char *p;

	/* 2.06 or later should support SAO */
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	/*
	 * Ensure we can ask for PROT_SAO.
	 * We can't really verify that it does the right thing, but at least we
	 * confirm the kernel will accept it.
	 */
	p = mmap(NULL, SIZE, PROT_READ | PROT_WRITE | PROT_SAO,
		 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	FAIL_IF(p == MAP_FAILED);

	/* Write to the mapping, to at least cause a fault */
	memset(p, 0xaa, SIZE);

	return 0;
}