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

__attribute__((used)) static int test_init(void)
{
	int loop = 1;
	int err = 0;

	while (loop--) {
#ifdef CONFIG_FSL_QMAN_TEST_STASH
		err = qman_test_stash();
		if (err)
			break;
#endif
#ifdef CONFIG_FSL_QMAN_TEST_API
		err = qman_test_api();
		if (err)
			break;
#endif
	}
	return err;
}