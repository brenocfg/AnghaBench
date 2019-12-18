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
 int /*<<< orphan*/  test_fail_message (int /*<<< orphan*/ *,char const*,int,char*,char const*,char*,char*,char*,void const*) ; 

int test_ptr_null(const char *file, int line, const char *s, const void *p)
{
    if (p == NULL)
        return 1;
    test_fail_message(NULL, file, line, "ptr", s, "NULL", "==", "%p", p);
    return 0;
}