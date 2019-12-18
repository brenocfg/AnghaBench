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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  clientctx ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  serverctx ; 
 int /*<<< orphan*/  test_func ; 
 char* test_get_argument (int) ; 

int setup_tests(void)
{
    char *cert, *pkey;

    if (!TEST_ptr(cert = test_get_argument(0))
            || !TEST_ptr(pkey = test_get_argument(1)))
        return 0;

    if (!create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                             TLS1_VERSION, 0,
                             &serverctx, &clientctx, cert, pkey)) {
        TEST_error("Failed to create SSL_CTX pair\n");
        return 0;
    }

    ADD_ALL_TESTS(test_func, 9);
    return 1;
}