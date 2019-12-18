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
struct TYPE_2__ {int ksft_pass; int ksft_fail; int ksft_xfail; int ksft_xpass; int ksft_xskip; int ksft_error; } ;

/* Variables and functions */
 TYPE_1__ ksft_cnt ; 
 scalar_t__ ksft_plan ; 
 int ksft_test_num () ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static inline void ksft_print_cnts(void)
{
	if (ksft_plan != ksft_test_num())
		printf("# Planned tests != run tests (%u != %u)\n",
			ksft_plan, ksft_test_num());
	printf("# Pass %d Fail %d Xfail %d Xpass %d Skip %d Error %d\n",
		ksft_cnt.ksft_pass, ksft_cnt.ksft_fail,
		ksft_cnt.ksft_xfail, ksft_cnt.ksft_xpass,
		ksft_cnt.ksft_xskip, ksft_cnt.ksft_error);
}