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
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  DTLS1_VERSION ; 
 int /*<<< orphan*/  DTLS_client_method () ; 
 int /*<<< orphan*/  DTLS_server_method () ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_has_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_read_ex (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  SSL_write_ex (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int test_ssl_pending(int tst)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    char msg[] = "A test message";
    char buf[5];
    size_t written, readbytes;

    if (tst == 0) {
        if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                           TLS_client_method(),
                                           TLS1_VERSION, 0,
                                           &sctx, &cctx, cert, privkey)))
            goto end;
    } else {
#ifndef OPENSSL_NO_DTLS
        if (!TEST_true(create_ssl_ctx_pair(DTLS_server_method(),
                                           DTLS_client_method(),
                                           DTLS1_VERSION, 0,
                                           &sctx, &cctx, cert, privkey)))
            goto end;
#else
        return 1;
#endif
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    if (!TEST_int_eq(SSL_pending(clientssl), 0)
            || !TEST_false(SSL_has_pending(clientssl))
            || !TEST_int_eq(SSL_pending(serverssl), 0)
            || !TEST_false(SSL_has_pending(serverssl))
            || !TEST_true(SSL_write_ex(serverssl, msg, sizeof(msg), &written))
            || !TEST_size_t_eq(written, sizeof(msg))
            || !TEST_true(SSL_read_ex(clientssl, buf, sizeof(buf), &readbytes))
            || !TEST_size_t_eq(readbytes, sizeof(buf))
            || !TEST_int_eq(SSL_pending(clientssl), (int)(written - readbytes))
            || !TEST_true(SSL_has_pending(clientssl)))
        goto end;

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}