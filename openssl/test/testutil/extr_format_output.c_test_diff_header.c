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
 int /*<<< orphan*/  test_printf_stderr (char*,char const*) ; 

__attribute__((used)) static void test_diff_header(const char *left, const char *right)
{
    test_printf_stderr("--- %s\n", left);
    test_printf_stderr("+++ %s\n", right);
}