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
struct shared_info {unsigned long amr1; unsigned long amr2; unsigned long amr3; unsigned long expected_iamr; unsigned long expected_uamor; unsigned long new_iamr; unsigned long new_uamor; int /*<<< orphan*/  child_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHILD_FAIL_IF (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKEY_DISABLE_EXECUTE ; 
 int /*<<< orphan*/  SPRN_AMR ; 
 int TEST_PASS ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long pkeyshift (int) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long,...) ; 
 int prod_parent (int /*<<< orphan*/ *) ; 
 int sys_pkey_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_pkey_free (int) ; 
 char* user_read ; 
 char* user_write ; 
 int wait_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int child(struct shared_info *info)
{
	unsigned long reg;
	bool disable_execute = true;
	int pkey1, pkey2, pkey3;
	int ret;

	/* Wait until parent fills out the initial register values. */
	ret = wait_parent(&info->child_sync);
	if (ret)
		return ret;

	/* Get some pkeys so that we can change their bits in the AMR. */
	pkey1 = sys_pkey_alloc(0, PKEY_DISABLE_EXECUTE);
	if (pkey1 < 0) {
		pkey1 = sys_pkey_alloc(0, 0);
		CHILD_FAIL_IF(pkey1 < 0, &info->child_sync);

		disable_execute = false;
	}

	pkey2 = sys_pkey_alloc(0, 0);
	CHILD_FAIL_IF(pkey2 < 0, &info->child_sync);

	pkey3 = sys_pkey_alloc(0, 0);
	CHILD_FAIL_IF(pkey3 < 0, &info->child_sync);

	info->amr1 |= 3ul << pkeyshift(pkey1);
	info->amr2 |= 3ul << pkeyshift(pkey2);
	info->amr3 |= info->amr2 | 3ul << pkeyshift(pkey3);

	if (disable_execute)
		info->expected_iamr |= 1ul << pkeyshift(pkey1);
	else
		info->expected_iamr &= ~(1ul << pkeyshift(pkey1));

	info->expected_iamr &= ~(1ul << pkeyshift(pkey2) | 1ul << pkeyshift(pkey3));

	info->expected_uamor |= 3ul << pkeyshift(pkey1) |
				3ul << pkeyshift(pkey2);
	info->new_iamr |= 1ul << pkeyshift(pkey1) | 1ul << pkeyshift(pkey2);
	info->new_uamor |= 3ul << pkeyshift(pkey1);

	/*
	 * We won't use pkey3. We just want a plausible but invalid key to test
	 * whether ptrace will let us write to AMR bits we are not supposed to.
	 *
	 * This also tests whether the kernel restores the UAMOR permissions
	 * after a key is freed.
	 */
	sys_pkey_free(pkey3);

	printf("%-30s AMR: %016lx pkey1: %d pkey2: %d pkey3: %d\n",
	       user_write, info->amr1, pkey1, pkey2, pkey3);

	mtspr(SPRN_AMR, info->amr1);

	/* Wait for parent to read our AMR value and write a new one. */
	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	ret = wait_parent(&info->child_sync);
	if (ret)
		return ret;

	reg = mfspr(SPRN_AMR);

	printf("%-30s AMR: %016lx\n", user_read, reg);

	CHILD_FAIL_IF(reg != info->amr2, &info->child_sync);

	/*
	 * Wait for parent to try to write an invalid AMR value.
	 */
	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	ret = wait_parent(&info->child_sync);
	if (ret)
		return ret;

	reg = mfspr(SPRN_AMR);

	printf("%-30s AMR: %016lx\n", user_read, reg);

	CHILD_FAIL_IF(reg != info->amr2, &info->child_sync);

	/*
	 * Wait for parent to try to write an IAMR and a UAMOR value. We can't
	 * verify them, but we can verify that the AMR didn't change.
	 */
	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	ret = wait_parent(&info->child_sync);
	if (ret)
		return ret;

	reg = mfspr(SPRN_AMR);

	printf("%-30s AMR: %016lx\n", user_read, reg);

	CHILD_FAIL_IF(reg != info->amr2, &info->child_sync);

	/* Now let parent now that we are finished. */

	ret = prod_parent(&info->child_sync);
	CHILD_FAIL_IF(ret, &info->child_sync);

	return TEST_PASS;
}