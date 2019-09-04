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
typedef  int /*<<< orphan*/  testdata ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 size_t MAX_ATTEMPTS ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_SYSCALL ; 
 int /*<<< orphan*/  SSL_alloc_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free_buffers (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int SSL_write (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  TEST_error (char*,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (char*,int,char const*,int) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clientctx ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverctx ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_func(int test)
{
    int result = 0;
    SSL *serverssl = NULL, *clientssl = NULL;
    int ret;
    size_t i, j;
    const char testdata[] = "Test data";
    char buf[sizeof(testdata)];

    if (!TEST_true(create_ssl_objects(serverctx, clientctx, &serverssl, &clientssl,
                                      NULL, NULL))) {
        TEST_error("Test %d failed: Create SSL objects failed\n", test);
        goto end;
    }

    if (!TEST_true(create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE))) {
        TEST_error("Test %d failed: Create SSL connection failed\n", test);
        goto end;
    }

    /*
     * Send and receive some test data. Do the whole thing twice to ensure
     * we hit at least one async event in both reading and writing
     */
    for (j = 0; j < 2; j++) {
        int len;

        /*

         * Write some test data. It should never take more than 2 attempts
         * (the first one might be a retryable fail).
         */
        for (ret = -1, i = 0, len = 0; len != sizeof(testdata) && i < 2;
             i++) {
            /* test == 0 mean to free/allocate = control */
            if (test >= 1 && !TEST_true(SSL_free_buffers(clientssl)))
                goto end;
            if (test >= 2 && !TEST_true(SSL_alloc_buffers(clientssl)))
                goto end;
            /* allocate a second time */
            if (test >= 3 && !TEST_true(SSL_alloc_buffers(clientssl)))
                goto end;
            if (test >= 4 && !TEST_true(SSL_free_buffers(clientssl)))
                goto end;

            ret = SSL_write(clientssl, testdata + len,
                            sizeof(testdata) - len);
            if (ret > 0) {
                len += ret;
            } else {
                int ssl_error = SSL_get_error(clientssl, ret);

                if (ssl_error == SSL_ERROR_SYSCALL ||
                    ssl_error == SSL_ERROR_SSL) {
                    TEST_error("Test %d failed: Failed to write app data\n", test);
                    goto end;
                }
            }
        }
        if (!TEST_size_t_eq(len, sizeof(testdata)))
            goto end;
        /*
         * Now read the test data. It may take more attempts here because
         * it could fail once for each byte read, including all overhead
         * bytes from the record header/padding etc.
         */
        for (ret = -1, i = 0, len = 0; len != sizeof(testdata) &&
                 i < MAX_ATTEMPTS; i++)
        {
            if (test >= 5 && !TEST_true(SSL_free_buffers(serverssl)))
                goto end;
            /* free a second time */
            if (test >= 6 && !TEST_true(SSL_free_buffers(serverssl)))
                goto end;
            if (test >= 7 && !TEST_true(SSL_alloc_buffers(serverssl)))
                goto end;
            if (test >= 8 && !TEST_true(SSL_free_buffers(serverssl)))
                goto end;

            ret = SSL_read(serverssl, buf + len, sizeof(buf) - len);
            if (ret > 0) {
                len += ret;
            } else {
                int ssl_error = SSL_get_error(serverssl, ret);

                if (ssl_error == SSL_ERROR_SYSCALL ||
                    ssl_error == SSL_ERROR_SSL) {
                    TEST_error("Test %d failed: Failed to read app data\n", test);
                    goto end;
                }
            }
        }
        if (!TEST_mem_eq(buf, len, testdata, sizeof(testdata)))
            goto end;
    }

    result = 1;
 end:
    if (!result)
        ERR_print_errors_fp(stderr);

    SSL_free(clientssl);
    SSL_free(serverssl);

    return result;
}