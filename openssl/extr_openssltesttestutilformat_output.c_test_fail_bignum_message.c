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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  test_fail_bignum_common (char const*,char const*,int,char const*,char const*,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_printf_stderr (char*) ; 

void test_fail_bignum_message(const char *prefix, const char *file,
                              int line, const char *type,
                              const char *left, const char *right,
                              const char *op,
                              const BIGNUM *bn1, const BIGNUM *bn2)
{
    test_fail_bignum_common(prefix, file, line, type, left, right, op, bn1, bn2);
    test_printf_stderr("\n");
}