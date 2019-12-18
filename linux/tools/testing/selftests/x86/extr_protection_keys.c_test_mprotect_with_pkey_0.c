#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {long size; int prot; } ;

/* Variables and functions */
 long HPAGE_SIZE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mprotect_pkey (int*,long,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* pkey_last_malloc_record ; 

void test_mprotect_with_pkey_0(int *ptr, u16 pkey)
{
	long size;
	int prot;

	assert(pkey_last_malloc_record);
	size = pkey_last_malloc_record->size;
	/*
	 * This is a bit of a hack.  But mprotect() requires
	 * huge-page-aligned sizes when operating on hugetlbfs.
	 * So, make sure that we use something that's a multiple
	 * of a huge page when we can.
	 */
	if (size >= HPAGE_SIZE)
		size = HPAGE_SIZE;
	prot = pkey_last_malloc_record->prot;

	/* Use pkey 0 */
	mprotect_pkey(ptr, size, prot, 0);

	/* Make sure that we can set it back to the original pkey. */
	mprotect_pkey(ptr, size, prot, pkey);
}