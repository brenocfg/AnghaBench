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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int CLONE_FILES ; 
 int CLONE_FS ; 
 int CLONE_VM ; 
 int /*<<< orphan*/  MEMFD_HUGE_STR ; 
 char* SHARED_FT_STR ; 
 int /*<<< orphan*/  abort () ; 
 unsigned long default_huge_page_size () ; 
 int hugetlbfs_test ; 
 int /*<<< orphan*/  join_idle_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memfd_str ; 
 unsigned long mfd_def_size ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spawn_idle_thread (int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_basic () ; 
 int /*<<< orphan*/  test_create () ; 
 int /*<<< orphan*/  test_seal_future_write () ; 
 int /*<<< orphan*/  test_seal_grow () ; 
 int /*<<< orphan*/  test_seal_resize () ; 
 int /*<<< orphan*/  test_seal_shrink () ; 
 int /*<<< orphan*/  test_seal_write () ; 
 int /*<<< orphan*/  test_share_dup (char*,char*) ; 
 int /*<<< orphan*/  test_share_fork (char*,char*) ; 
 int /*<<< orphan*/  test_share_mmap (char*,char*) ; 
 int /*<<< orphan*/  test_share_open (char*,char*) ; 

int main(int argc, char **argv)
{
	pid_t pid;

	if (argc == 2) {
		if (!strcmp(argv[1], "hugetlbfs")) {
			unsigned long hpage_size = default_huge_page_size();

			if (!hpage_size) {
				printf("Unable to determine huge page size\n");
				abort();
			}

			hugetlbfs_test = 1;
			memfd_str = MEMFD_HUGE_STR;
			mfd_def_size = hpage_size * 2;
		} else {
			printf("Unknown option: %s\n", argv[1]);
			abort();
		}
	}

	test_create();
	test_basic();

	test_seal_write();
	test_seal_future_write();
	test_seal_shrink();
	test_seal_grow();
	test_seal_resize();

	test_share_dup("SHARE-DUP", "");
	test_share_mmap("SHARE-MMAP", "");
	test_share_open("SHARE-OPEN", "");
	test_share_fork("SHARE-FORK", "");

	/* Run test-suite in a multi-threaded environment with a shared
	 * file-table. */
	pid = spawn_idle_thread(CLONE_FILES | CLONE_FS | CLONE_VM);
	test_share_dup("SHARE-DUP", SHARED_FT_STR);
	test_share_mmap("SHARE-MMAP", SHARED_FT_STR);
	test_share_open("SHARE-OPEN", SHARED_FT_STR);
	test_share_fork("SHARE-FORK", SHARED_FT_STR);
	join_idle_thread(pid);

	printf("memfd: DONE\n");

	return 0;
}