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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  test_fail_message_prefix (char const*,char const*,int,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  test_flush_stderr () ; 
 int /*<<< orphan*/  test_printf_stderr (char*) ; 
 int /*<<< orphan*/  test_vprintf_stderr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_fail_message_va(const char *prefix, const char *file,
                                 int line, const char *type,
                                 const char *left, const char *right,
                                 const char *op, const char *fmt, va_list ap)
{
    test_fail_message_prefix(prefix, file, line, type, left, right, op);
    if (fmt != NULL) {
        test_vprintf_stderr(fmt, ap);
        test_printf_stderr("\n");
    }
    test_flush_stderr();
}