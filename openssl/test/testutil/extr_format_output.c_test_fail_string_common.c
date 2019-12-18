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
 int MAX_STRING_WIDTH ; 
 scalar_t__ isprint (unsigned char) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int subtest_level () ; 
 int /*<<< orphan*/  test_diff_header (char const*,char const*) ; 
 int /*<<< orphan*/  test_fail_message_prefix (char const*,char const*,int,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  test_flush_stderr () ; 
 int /*<<< orphan*/  test_printf_stderr (char*,...) ; 
 int /*<<< orphan*/  test_string_null_empty (char const*,char) ; 

__attribute__((used)) static void test_fail_string_common(const char *prefix, const char *file,
                                    int line, const char *type,
                                    const char *left, const char *right,
                                    const char *op, const char *m1, size_t l1,
                                    const char *m2, size_t l2)
{
    const size_t width = (MAX_STRING_WIDTH - subtest_level() - 12) / 16 * 16;
    char b1[MAX_STRING_WIDTH + 1], b2[MAX_STRING_WIDTH + 1];
    char bdiff[MAX_STRING_WIDTH + 1];
    size_t n1, n2, i;
    unsigned int cnt = 0, diff;

    test_fail_message_prefix(prefix, file, line, type, left, right, op);
    if (m1 == NULL)
        l1 = 0;
    if (m2 == NULL)
        l2 = 0;
    if (l1 == 0 && l2 == 0) {
        if ((m1 == NULL) == (m2 == NULL)) {
            test_string_null_empty(m1, ' ');
        } else {
            test_diff_header(left, right);
            test_string_null_empty(m1, '-');
            test_string_null_empty(m2, '+');
        }
        goto fin;
    }

    if (l1 != l2 || strcmp(m1, m2) != 0)
        test_diff_header(left, right);

    while (l1 > 0 || l2 > 0) {
        n1 = n2 = 0;
        if (l1 > 0) {
            b1[n1 = l1 > width ? width : l1] = 0;
            for (i = 0; i < n1; i++)
                b1[i] = isprint((unsigned char)m1[i]) ? m1[i] : '.';
        }
        if (l2 > 0) {
            b2[n2 = l2 > width ? width : l2] = 0;
            for (i = 0; i < n2; i++)
                b2[i] = isprint((unsigned char)m2[i]) ? m2[i] : '.';
        }
        diff = 0;
        i = 0;
        if (n1 > 0 && n2 > 0) {
            const size_t j = n1 < n2 ? n1 : n2;

            for (; i < j; i++)
                if (m1[i] == m2[i]) {
                    bdiff[i] = ' ';
                } else {
                    bdiff[i] = '^';
                    diff = 1;
                }
            bdiff[i] = '\0';
        }
        if (n1 == n2 && !diff) {
            test_printf_stderr("%4u:  '%s'\n", cnt, n2 > n1 ? b2 : b1);
        } else {
            if (cnt == 0 && (m1 == NULL || *m1 == '\0'))
                test_string_null_empty(m1, '-');
            else if (n1 > 0)
                test_printf_stderr("%4u:- '%s'\n", cnt, b1);
            if (cnt == 0 && (m2 == NULL || *m2 == '\0'))
               test_string_null_empty(m2, '+');
            else if (n2 > 0)
                test_printf_stderr("%4u:+ '%s'\n", cnt, b2);
            if (diff && i > 0)
                test_printf_stderr("%4s    %s\n", "", bdiff);
        }
        m1 += n1;
        m2 += n2;
        l1 -= n1;
        l2 -= n2;
        cnt += width;
    }
fin:
    test_flush_stderr();
}