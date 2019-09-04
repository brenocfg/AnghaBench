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
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_ciphersuites (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_set_ciphersuites (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int test_set_ciphersuite(int idx)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    int testresult = 0;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey))
            || !TEST_true(SSL_CTX_set_ciphersuites(sctx,
                           "TLS_AES_128_GCM_SHA256:TLS_AES_128_CCM_SHA256")))
        goto end;

    if (idx >=4 && idx <= 7) {
        /* SSL_CTX explicit cipher list */
        if (!TEST_true(SSL_CTX_set_cipher_list(cctx, "AES256-GCM-SHA384")))
            goto end;
    }

    if (idx == 0 || idx == 4) {
        /* Default ciphersuite */
        if (!TEST_true(SSL_CTX_set_ciphersuites(cctx,
                                                "TLS_AES_128_GCM_SHA256")))
            goto end;
    } else if (idx == 1 || idx == 5) {
        /* Non default ciphersuite */
        if (!TEST_true(SSL_CTX_set_ciphersuites(cctx,
                                                "TLS_AES_128_CCM_SHA256")))
            goto end;
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                          &clientssl, NULL, NULL)))
        goto end;

    if (idx == 8 || idx == 9) {
        /* SSL explicit cipher list */
        if (!TEST_true(SSL_set_cipher_list(clientssl, "AES256-GCM-SHA384")))
            goto end;
    }

    if (idx == 2 || idx == 6 || idx == 8) {
        /* Default ciphersuite */
        if (!TEST_true(SSL_set_ciphersuites(clientssl,
                                            "TLS_AES_128_GCM_SHA256")))
            goto end;
    } else if (idx == 3 || idx == 7 || idx == 9) {
        /* Non default ciphersuite */
        if (!TEST_true(SSL_set_ciphersuites(clientssl,
                                            "TLS_AES_128_CCM_SHA256")))
            goto end;
    }

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