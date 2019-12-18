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
struct shared_info {unsigned long amr; unsigned long iamr; unsigned long uamor; int /*<<< orphan*/  core_time; int /*<<< orphan*/  child_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  PKEY_DISABLE_EXECUTE ; 
 int /*<<< orphan*/  SPRN_AMR ; 
 int TEST_FAIL ; 
 int increase_core_file_limit () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long pkeyshift (int) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long,int,int,int) ; 
 int sys_pkey_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_pkey_free (int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 char* user_write ; 
 int wait_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int child(struct shared_info *info)
{
	bool disable_execute = true;
	int pkey1, pkey2, pkey3;
	int *ptr, ret;

	/* Wait until parent fills out the initial register values. */
	ret = wait_parent(&info->child_sync);
	if (ret)
		return ret;

	ret = increase_core_file_limit();
	FAIL_IF(ret);

	/* Get some pkeys so that we can change their bits in the AMR. */
	pkey1 = sys_pkey_alloc(0, PKEY_DISABLE_EXECUTE);
	if (pkey1 < 0) {
		pkey1 = sys_pkey_alloc(0, 0);
		FAIL_IF(pkey1 < 0);

		disable_execute = false;
	}

	pkey2 = sys_pkey_alloc(0, 0);
	FAIL_IF(pkey2 < 0);

	pkey3 = sys_pkey_alloc(0, 0);
	FAIL_IF(pkey3 < 0);

	info->amr |= 3ul << pkeyshift(pkey1) | 2ul << pkeyshift(pkey2);

	if (disable_execute)
		info->iamr |= 1ul << pkeyshift(pkey1);
	else
		info->iamr &= ~(1ul << pkeyshift(pkey1));

	info->iamr &= ~(1ul << pkeyshift(pkey2) | 1ul << pkeyshift(pkey3));

	info->uamor |= 3ul << pkeyshift(pkey1) | 3ul << pkeyshift(pkey2);

	printf("%-30s AMR: %016lx pkey1: %d pkey2: %d pkey3: %d\n",
	       user_write, info->amr, pkey1, pkey2, pkey3);

	mtspr(SPRN_AMR, info->amr);

	/*
	 * We won't use pkey3. This tests whether the kernel restores the UAMOR
	 * permissions after a key is freed.
	 */
	sys_pkey_free(pkey3);

	info->core_time = time(NULL);

	/* Crash. */
	ptr = 0;
	*ptr = 1;

	/* Shouldn't get here. */
	FAIL_IF(true);

	return TEST_FAIL;
}