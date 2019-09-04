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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MADV_DONTNEED ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PROT_EXEC ; 
 int /*<<< orphan*/  do_not_expect_pk_fault (char*) ; 
 int /*<<< orphan*/  dprintf2 (char*,void*,...) ; 
 int /*<<< orphan*/  expected_pk_fault (scalar_t__) ; 
 void* get_pointer_to_instructions () ; 
 int /*<<< orphan*/  lots_o_noops_around_write (int*) ; 
 int /*<<< orphan*/  madvise (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mprotect_pkey (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_access_deny (scalar_t__) ; 
 int /*<<< orphan*/  pkey_assert (int) ; 
 int /*<<< orphan*/  rdpkru () ; 
 int read_ptr (void*) ; 

void test_executing_on_unreadable_memory(int *ptr, u16 pkey)
{
	void *p1;
	int scratch;
	int ptr_contents;
	int ret;

	p1 = get_pointer_to_instructions();
	lots_o_noops_around_write(&scratch);
	ptr_contents = read_ptr(p1);
	dprintf2("ptr (%p) contents@%d: %x\n", p1, __LINE__, ptr_contents);

	ret = mprotect_pkey(p1, PAGE_SIZE, PROT_EXEC, (u64)pkey);
	pkey_assert(!ret);
	pkey_access_deny(pkey);

	dprintf2("pkru: %x\n", rdpkru());

	/*
	 * Make sure this is an *instruction* fault
	 */
	madvise(p1, PAGE_SIZE, MADV_DONTNEED);
	lots_o_noops_around_write(&scratch);
	do_not_expect_pk_fault("executing on PROT_EXEC memory");
	ptr_contents = read_ptr(p1);
	dprintf2("ptr (%p) contents@%d: %x\n", p1, __LINE__, ptr_contents);
	expected_pk_fault(pkey);
}