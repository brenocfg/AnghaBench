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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 size_t MAX_ATTEMPTS ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_SYSCALL ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int SSL_write (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_mem_eq (char const*,int,char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  bio_f_async_filter () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fragment ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int test_asyncio(int test)
{
    SSL_CTX *serverctx = NULL, *clientctx = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    BIO *s_to_c_fbio = NULL, *c_to_s_fbio = NULL;
    int testresult = 0, ret;
    size_t i, j;
    const char testdata[] = "Test data";
    char buf[sizeof(testdata)];

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &serverctx, &clientctx, cert, privkey)))
        goto end;

    /*
     * We do 2 test runs. The first time around we just do a normal handshake
     * with lots of async io going on. The second time around we also break up
     * all records so that the content is only one byte length (up until the
     * CCS)
     */
    if (test == 1)
        fragment = 1;


    s_to_c_fbio = BIO_new(bio_f_async_filter());
    c_to_s_fbio = BIO_new(bio_f_async_filter());
    if (!TEST_ptr(s_to_c_fbio)
            || !TEST_ptr(c_to_s_fbio)) {
        BIO_free(s_to_c_fbio);
        BIO_free(c_to_s_fbio);
        goto end;
    }

    /* BIOs get freed on error */
    if (!TEST_true(create_ssl_objects(serverctx, clientctx, &serverssl,
                                      &clientssl, s_to_c_fbio, c_to_s_fbio))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                          SSL_ERROR_NONE)))
        goto end;

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
            ret = SSL_write(clientssl, testdata + len,
                sizeof(testdata) - len);
            if (ret > 0) {
                len += ret;
            } else {
                int ssl_error = SSL_get_error(clientssl, ret);

                if (!TEST_false(ssl_error == SSL_ERROR_SYSCALL ||
                                ssl_error == SSL_ERROR_SSL))
                    goto end;
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
                i < MAX_ATTEMPTS; i++) {
            ret = SSL_read(serverssl, buf + len, sizeof(buf) - len);
            if (ret > 0) {
                len += ret;
            } else {
                int ssl_error = SSL_get_error(serverssl, ret);

                if (!TEST_false(ssl_error == SSL_ERROR_SYSCALL ||
                                ssl_error == SSL_ERROR_SSL))
                    goto end;
            }
        }
        if (!TEST_mem_eq(testdata, sizeof(testdata), buf, len))
            goto end;
    }

    /* Also frees the BIOs */
    SSL_free(clientssl);
    SSL_free(serverssl);
    clientssl = serverssl = NULL;

    testresult = 1;

 end:
    SSL_free(clientssl);
    SSL_free(serverssl);
    SSL_CTX_free(clientctx);
    SSL_CTX_free(serverctx);

    return testresult;
}