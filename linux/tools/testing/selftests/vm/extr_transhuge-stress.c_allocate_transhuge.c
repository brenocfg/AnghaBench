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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 int HPAGE_SHIFT ; 
 int /*<<< orphan*/  HPAGE_SIZE ; 
 int /*<<< orphan*/  MADV_HUGEPAGE ; 
 int MAP_ANONYMOUS ; 
 int MAP_FIXED ; 
 int MAP_NORESERVE ; 
 int MAP_PRIVATE ; 
 int PAGEMAP_PFN (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGEMAP_PRESENT (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ madvise (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (void*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagemap_fd ; 
 int pread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,uintptr_t) ; 

int64_t allocate_transhuge(void *ptr)
{
	uint64_t ent[2];

	/* drop pmd */
	if (mmap(ptr, HPAGE_SIZE, PROT_READ | PROT_WRITE,
				MAP_FIXED | MAP_ANONYMOUS |
				MAP_NORESERVE | MAP_PRIVATE, -1, 0) != ptr)
		errx(2, "mmap transhuge");

	if (madvise(ptr, HPAGE_SIZE, MADV_HUGEPAGE))
		err(2, "MADV_HUGEPAGE");

	/* allocate transparent huge page */
	*(volatile void **)ptr = ptr;

	if (pread(pagemap_fd, ent, sizeof(ent),
			(uintptr_t)ptr >> (PAGE_SHIFT - 3)) != sizeof(ent))
		err(2, "read pagemap");

	if (PAGEMAP_PRESENT(ent[0]) && PAGEMAP_PRESENT(ent[1]) &&
	    PAGEMAP_PFN(ent[0]) + 1 == PAGEMAP_PFN(ent[1]) &&
	    !(PAGEMAP_PFN(ent[0]) & ((1 << (HPAGE_SHIFT - PAGE_SHIFT)) - 1)))
		return PAGEMAP_PFN(ent[0]);

	return -1;
}