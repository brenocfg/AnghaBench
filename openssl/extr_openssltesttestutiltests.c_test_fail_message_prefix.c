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

void test_fail_message_prefix(const char *prefix, const char *file,
                              int line, const char *type,
                              const char *left, const char *right,
                              const char *op)
{
    test_printf_stderr("%s: ", prefix != NULL ? prefix : "ERROR");
    if (type)
        test_printf_stderr("(%s) ", type);
    if (op != NULL) {
        if (left != NULL && right != NULL)
            test_printf_stderr("'%s %s %s' failed", left, op, right);
        else
            test_printf_stderr("'%s'", op);
    }
    if (file != NULL) {
        test_printf_stderr(" @ %s:%d", file, line);
    }
    test_printf_stderr("\n");
}