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
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  test_empty ; 
 int /*<<< orphan*/  test_unsupported ; 
 int /*<<< orphan*/  test_v2 ; 
 int /*<<< orphan*/  test_v3 ; 

int setup_tests(void)
{
    if (!TEST_ptr(ctx = SSL_CTX_new(TLS_server_method()))
            || !TEST_ptr(s = SSL_new(ctx)))
        return 0;

    ADD_TEST(test_empty);
    ADD_TEST(test_unsupported);
    ADD_TEST(test_v2);
    ADD_TEST(test_v3);
    return 1;
}