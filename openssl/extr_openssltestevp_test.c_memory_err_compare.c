#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* err; int /*<<< orphan*/ * expected_err; } ;
typedef  TYPE_1__ EVP_TEST ;

/* Variables and functions */
 int TEST_mem_eq (void const*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  TEST_mem_ne (void const*,size_t,void const*,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int memory_err_compare(EVP_TEST *t, const char *err,
                              const void *expected, size_t expected_len,
                              const void *got, size_t got_len)
{
    int r;

    if (t->expected_err != NULL && strcmp(t->expected_err, err) == 0)
        r = !TEST_mem_ne(expected, expected_len, got, got_len);
    else
        r = TEST_mem_eq(expected, expected_len, got, got_len);
    if (!r)
        t->err = err;
    return r;
}