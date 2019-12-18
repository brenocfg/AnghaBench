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
typedef  enum kmod_test_case { ____Placeholder_kmod_test_case } kmod_test_case ;

/* Variables and functions */
#define  TEST_KMOD_DRIVER 129 
#define  TEST_KMOD_FS_TYPE 128 

__attribute__((used)) static const char *test_case_str(enum kmod_test_case test_case)
{
	switch (test_case) {
	case TEST_KMOD_DRIVER:
		return "TEST_KMOD_DRIVER";
	case TEST_KMOD_FS_TYPE:
		return "TEST_KMOD_FS_TYPE";
	default:
		return "invalid";
	}
}