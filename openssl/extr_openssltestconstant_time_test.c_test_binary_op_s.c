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
 int /*<<< orphan*/  CONSTTIME_FALSE_S ; 
 int /*<<< orphan*/  CONSTTIME_TRUE_S ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_eq (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_binary_op_s(size_t (*op) (size_t a, size_t b),
                            const char *op_name, size_t a, size_t b,
                            int is_true)
{
    if (is_true && !TEST_size_t_eq(op(a,b), CONSTTIME_TRUE_S))
        return 0;
    if (!is_true && !TEST_uint_eq(op(a,b), CONSTTIME_FALSE_S))
        return 0;
    return 1;
}