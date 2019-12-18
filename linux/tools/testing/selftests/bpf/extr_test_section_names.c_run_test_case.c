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
struct sec_name_test {int dummy; } ;

/* Variables and functions */
 scalar_t__ test_attach_type_by_name (struct sec_name_test const*) ; 
 scalar_t__ test_prog_type_by_name (struct sec_name_test const*) ; 

__attribute__((used)) static int run_test_case(const struct sec_name_test *test)
{
	if (test_prog_type_by_name(test))
		return -1;
	if (test_attach_type_by_name(test))
		return -1;
	return 0;
}