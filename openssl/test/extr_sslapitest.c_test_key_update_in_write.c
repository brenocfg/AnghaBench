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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_REQUESTED ; 
 int /*<<< orphan*/  SSL_do_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_key_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SSL_set0_wbio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  bio_s_always_retry () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 int strlen (char*) ; 

__attribute__((used)) static int test_key_update_in_write(int tst)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    char buf[20];
    static char *mess = "A test message";
    BIO *bretry = BIO_new(bio_s_always_retry());
    BIO *tmp = NULL;
    SSL *peerupdate = NULL, *peerwrite = NULL;

    if (!TEST_ptr(bretry)
            || !TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                              TLS_client_method(),
                                              TLS1_3_VERSION,
                                              0,
                                              &sctx, &cctx, cert, privkey))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    peerupdate = tst == 0 ? clientssl : serverssl;
    peerwrite = tst == 0 ? serverssl : clientssl;

    if (!TEST_true(SSL_key_update(peerupdate, SSL_KEY_UPDATE_REQUESTED))
            || !TEST_true(SSL_do_handshake(peerupdate)))
        goto end;

    /* Swap the writing endpoint's write BIO to force a retry */
    tmp = SSL_get_wbio(peerwrite);
    if (!TEST_ptr(tmp) || !TEST_true(BIO_up_ref(tmp))) {
        tmp = NULL;
        goto end;
    }
    SSL_set0_wbio(peerwrite, bretry);
    bretry = NULL;

    /* Write data that we know will fail with SSL_ERROR_WANT_WRITE */
    if (!TEST_int_eq(SSL_write(peerwrite, mess, strlen(mess)), -1)
            || !TEST_int_eq(SSL_get_error(peerwrite, 0), SSL_ERROR_WANT_WRITE))
        goto end;

    /* Reinstate the original writing endpoint's write BIO */
    SSL_set0_wbio(peerwrite, tmp);
    tmp = NULL;

    /* Now read some data - we will read the key update */
    if (!TEST_int_eq(SSL_read(peerwrite, buf, sizeof(buf)), -1)
            || !TEST_int_eq(SSL_get_error(peerwrite, 0), SSL_ERROR_WANT_READ))
        goto end;

    /*
     * Complete the write we started previously and read it from the other
     * endpoint
     */
    if (!TEST_int_eq(SSL_write(peerwrite, mess, strlen(mess)), strlen(mess))
            || !TEST_int_eq(SSL_read(peerupdate, buf, sizeof(buf)), strlen(mess)))
        goto end;

    /* Write more data to ensure we send the KeyUpdate message back */
    if (!TEST_int_eq(SSL_write(peerwrite, mess, strlen(mess)), strlen(mess))
            || !TEST_int_eq(SSL_read(peerupdate, buf, sizeof(buf)), strlen(mess)))
        goto end;

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    BIO_free(bretry);
    BIO_free(tmp);

    return testresult;
}