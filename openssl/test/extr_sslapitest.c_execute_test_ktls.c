#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  rbio; int /*<<< orphan*/  wbio; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_get_ktls_recv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_get_ktls_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_MODE_NO_KTLS_RX ; 
 int /*<<< orphan*/  SSL_MODE_NO_KTLS_TX ; 
 int /*<<< orphan*/  SSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_set_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__**,int,int) ; 
 int /*<<< orphan*/  create_test_sockets (int*,int*) ; 
 int /*<<< orphan*/  ktls_chk_platform (int) ; 
 int /*<<< orphan*/  ping_pong_query (TYPE_1__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int execute_test_ktls(int cis_ktls_tx, int cis_ktls_rx,
                             int sis_ktls_tx, int sis_ktls_rx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;
    int cfd, sfd;

    if (!TEST_true(create_test_sockets(&cfd, &sfd)))
        goto end;

    /* Skip this test if the platform does not support ktls */
    if (!ktls_chk_platform(cfd))
        return 1;

    /* Create a session based on SHA-256 */
    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       TLS1_2_VERSION, TLS1_2_VERSION,
                                       &sctx, &cctx, cert, privkey))
            || !TEST_true(SSL_CTX_set_cipher_list(cctx,
                                                  "AES128-GCM-SHA256"))
            || !TEST_true(create_ssl_objects2(sctx, cctx, &serverssl,
                                          &clientssl, sfd, cfd)))
        goto end;

    if (!cis_ktls_tx) {
        if (!TEST_true(SSL_set_mode(clientssl, SSL_MODE_NO_KTLS_TX)))
            goto end;
    }

    if (!sis_ktls_tx) {
        if (!TEST_true(SSL_set_mode(serverssl, SSL_MODE_NO_KTLS_TX)))
            goto end;
    }

    if (!cis_ktls_rx) {
        if (!TEST_true(SSL_set_mode(clientssl, SSL_MODE_NO_KTLS_RX)))
            goto end;
    }

    if (!sis_ktls_rx) {
        if (!TEST_true(SSL_set_mode(serverssl, SSL_MODE_NO_KTLS_RX)))
            goto end;
    }

    if (!TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    if (!cis_ktls_tx) {
        if (!TEST_false(BIO_get_ktls_send(clientssl->wbio)))
            goto end;
    } else {
        if (!TEST_true(BIO_get_ktls_send(clientssl->wbio)))
            goto end;
    }

    if (!sis_ktls_tx) {
        if (!TEST_false(BIO_get_ktls_send(serverssl->wbio)))
            goto end;
    } else {
        if (!TEST_true(BIO_get_ktls_send(serverssl->wbio)))
            goto end;
    }

    if (!cis_ktls_rx) {
        if (!TEST_false(BIO_get_ktls_recv(clientssl->rbio)))
            goto end;
    } else {
        if (!TEST_true(BIO_get_ktls_recv(clientssl->rbio)))
            goto end;
    }

    if (!sis_ktls_rx) {
        if (!TEST_false(BIO_get_ktls_recv(serverssl->rbio)))
            goto end;
    } else {
        if (!TEST_true(BIO_get_ktls_recv(serverssl->rbio)))
            goto end;
    }

    if (!TEST_true(ping_pong_query(clientssl, serverssl, cfd, sfd)))
        goto end;

    testresult = 1;
end:
    if (clientssl) {
        SSL_shutdown(clientssl);
        SSL_free(clientssl);
    }
    if (serverssl) {
        SSL_shutdown(serverssl);
        SSL_free(serverssl);
    }
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    serverssl = clientssl = NULL;
    return testresult;
}