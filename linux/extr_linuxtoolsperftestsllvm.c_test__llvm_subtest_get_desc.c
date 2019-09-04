#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* desc; } ;

/* Variables and functions */
 int __LLVM_TESTCASE_MAX ; 
 TYPE_1__* bpf_source_table ; 

const char *test__llvm_subtest_get_desc(int subtest)
{
	if ((subtest < 0) || (subtest >= __LLVM_TESTCASE_MAX))
		return NULL;

	return bpf_source_table[subtest].desc;
}