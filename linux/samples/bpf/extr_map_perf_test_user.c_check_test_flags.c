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
typedef  enum test_type { ____Placeholder_test_type } test_type ;

/* Variables and functions */
 int TEST_BIT (int) ; 
 int test_flags ; 

__attribute__((used)) static int check_test_flags(enum test_type t)
{
	return test_flags & TEST_BIT(t);
}