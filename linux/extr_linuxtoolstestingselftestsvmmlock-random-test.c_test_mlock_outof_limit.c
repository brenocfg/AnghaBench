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
struct rlimit {int rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLOCK_ONFAULT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int TEST_LOOP ; 
 int get_proc_locked_vm_size () ; 
 int /*<<< orphan*/  getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int mlock (char*,int) ; 
 int mlock2_ (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int test_mlock_outof_limit(char *p, int alloc_size)
{
	int i;
	int ret = 0;
	int locked_vm_size = 0, old_locked_vm_size = 0;
	struct rlimit cur;

	getrlimit(RLIMIT_MEMLOCK, &cur);
	if (cur.rlim_cur >= alloc_size) {
		printf("alloc_size[%d] >%u rlimit, violates test condition\n",
				alloc_size, (unsigned int)cur.rlim_cur);
		return -1;
	}

	old_locked_vm_size = get_proc_locked_vm_size();
	srand(time(NULL));
	for (i = 0; i < TEST_LOOP; i++) {
		int is_mlock = !!(rand() % 2);
		int lock_size = (rand() % (alloc_size - cur.rlim_cur))
			+ cur.rlim_cur;
		int start_offset = rand() % (alloc_size - lock_size);

		if (is_mlock)
			ret = mlock(p + start_offset, lock_size);
		else
			ret = mlock2_(p + start_offset, lock_size,
					MLOCK_ONFAULT);
		if (ret == 0) {
			printf("%s() succeeds? on %p(%d) mlock%p(%d)\n",
					is_mlock ? "mlock" : "mlock2",
					p, alloc_size,
					p + start_offset, lock_size);
			return -1;
		}
	}

	locked_vm_size = get_proc_locked_vm_size();
	if (locked_vm_size != old_locked_vm_size) {
		printf("tests leads to new mlocked page: old[%d], new[%d]\n",
				old_locked_vm_size,
				locked_vm_size);
		return -1;
	}

	return 0;
}