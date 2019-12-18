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
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_cert_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int SSL_set1_sigalgs_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert_cb ; 
 int cert_cb_cnt ; 
 int create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_cert_cb_int(int prot, int tst)
{
    SSL_CTX *cctx = NULL, *sctx = NULL, *snictx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0, ret;

#ifdef OPENSSL_NO_EC
    /* We use an EC cert in these tests, so we skip in a no-ec build */
    if (tst >= 3)
        return 1;
#endif

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       TLS1_VERSION,
                                       prot,
                                       &sctx, &cctx, NULL, NULL)))
        goto end;

    if (tst == 0)
        cert_cb_cnt = -1;
    else if (tst >= 3)
        cert_cb_cnt = 3;
    else
        cert_cb_cnt = 0;

    if (tst == 2)
        snictx = SSL_CTX_new(TLS_server_method());
    SSL_CTX_set_cert_cb(sctx, cert_cb, snictx);

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                      NULL, NULL)))
        goto end;

    if (tst == 4) {
        /*
         * We cause SSL_check_chain() to fail by specifying sig_algs that
         * the chain doesn't meet (the root uses an RSA cert)
         */
        if (!TEST_true(SSL_set1_sigalgs_list(clientssl,
                                             "ecdsa_secp256r1_sha256")))
            goto end;
    } else if (tst == 5) {
        /*
         * We cause SSL_check_chain() to fail by specifying sig_algs that
         * the ee cert doesn't meet (the ee uses an ECDSA cert)
         */
        if (!TEST_true(SSL_set1_sigalgs_list(clientssl,
                           "rsa_pss_rsae_sha256:rsa_pkcs1_sha256")))
            goto end;
    }

    ret = create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE);
    if (!TEST_true(tst == 0 || tst == 4 || tst == 5 ? !ret : ret)
            || (tst > 0
                && !TEST_int_eq((cert_cb_cnt - 2) * (cert_cb_cnt - 3), 0))) {
        goto end;
    }

    testresult = 1;

 end:
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    SSL_CTX_free(snictx);

    return testresult;
}