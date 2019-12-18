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
typedef  int /*<<< orphan*/  root ;
struct TYPE_3__ {int (* fn ) (char*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
#define  KSFT_PASS 129 
#define  KSFT_SKIP 128 
 int PATH_MAX ; 
 scalar_t__ cg_find_unified_root (char*,int) ; 
 scalar_t__ cg_read_strstr (char*,char*,char*) ; 
 scalar_t__ cg_write (char*,char*,char*) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  ksft_test_result_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_test_result_skip (char*,int /*<<< orphan*/ ) ; 
 int stub1 (char*) ; 
 TYPE_1__* tests ; 

int main(int argc, char *argv[])
{
	char root[PATH_MAX];
	int i, ret = EXIT_SUCCESS;

	if (cg_find_unified_root(root, sizeof(root)))
		ksft_exit_skip("cgroup v2 isn't mounted\n");

	if (cg_read_strstr(root, "cgroup.subtree_control", "memory"))
		if (cg_write(root, "cgroup.subtree_control", "+memory"))
			ksft_exit_skip("Failed to set memory controller\n");

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		switch (tests[i].fn(root)) {
		case KSFT_PASS:
			ksft_test_result_pass("%s\n", tests[i].name);
			break;
		case KSFT_SKIP:
			ksft_test_result_skip("%s\n", tests[i].name);
			break;
		default:
			ret = EXIT_FAILURE;
			ksft_test_result_fail("%s\n", tests[i].name);
			break;
		}
	}

	return ret;
}