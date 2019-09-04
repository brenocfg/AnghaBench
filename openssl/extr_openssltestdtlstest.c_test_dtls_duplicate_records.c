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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTLS1_VERSION ; 
 int /*<<< orphan*/  DTLS_client_method () ; 
 int /*<<< orphan*/  DTLS_server_method () ; 
 int /*<<< orphan*/  DTLS_set_timer_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMPACKET_CTRL_SET_DUPLICATE_REC ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_wbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  timer_cb ; 

__attribute__((used)) static int test_dtls_duplicate_records(void)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    int testresult = 0;

    if (!TEST_true(create_ssl_ctx_pair(DTLS_server_method(),
                                       DTLS_client_method(),
                                       DTLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey)))
        return 0;

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, NULL)))
        goto end;

    DTLS_set_timer_cb(clientssl, timer_cb);
    DTLS_set_timer_cb(serverssl, timer_cb);

    BIO_ctrl(SSL_get_wbio(clientssl), MEMPACKET_CTRL_SET_DUPLICATE_REC, 1, NULL);
    BIO_ctrl(SSL_get_wbio(serverssl), MEMPACKET_CTRL_SET_DUPLICATE_REC, 1, NULL);

    if (!TEST_true(create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE)))
        goto end;

    testresult = 1;
 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}