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
 int /*<<< orphan*/  test_printf_stderr (char*,...) ; 

__attribute__((used)) static void test_memory_null_empty(const unsigned char *m, char c)
{
    if (m == NULL)
        test_printf_stderr("%4s %c%s\n", "", c, "NULL");
    else
        test_printf_stderr("%04x %c%s\n", 0u, c, "empty");
}