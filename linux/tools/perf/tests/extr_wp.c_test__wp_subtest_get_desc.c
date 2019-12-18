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
struct TYPE_3__ {char const* desc; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* wp_testcase_table ; 

const char *test__wp_subtest_get_desc(int i)
{
	if (i < 0 || i >= (int)ARRAY_SIZE(wp_testcase_table))
		return NULL;
	return wp_testcase_table[i].desc;
}