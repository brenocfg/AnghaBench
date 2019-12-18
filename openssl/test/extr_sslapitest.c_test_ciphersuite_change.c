#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_2__ const* cipher; int /*<<< orphan*/  cipher_id; } ;
typedef  TYPE_1__ SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  TYPE_2__ SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_ciphersuites (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_ERROR_SSL ; 
 int /*<<< orphan*/  SSL_ERROR_WANT_READ ; 
 int /*<<< orphan*/  SSL_R_CIPHERSUITE_DIGEST_HAS_CHANGED ; 
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_1__*) ; 
 TYPE_2__* SSL_SESSION_get0_cipher (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_session_reused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int test_ciphersuite_change(void)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    SSL_SESSION *clntsess = NULL;
    int testresult = 0;
    const SSL_CIPHER *aes_128_gcm_sha256 = NULL;

    /* Create a session based on SHA-256 */
    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, cert, privkey))
            || !TEST_true(SSL_CTX_set_ciphersuites(cctx,
                                                   "TLS_AES_128_GCM_SHA256"))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                          &clientssl, NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    clntsess = SSL_get1_session(clientssl);
    /* Save for later */
    aes_128_gcm_sha256 = SSL_SESSION_get0_cipher(clntsess);
    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;

# if !defined(OPENSSL_NO_CHACHA) && !defined(OPENSSL_NO_POLY1305)
    /* Check we can resume a session with a different SHA-256 ciphersuite */
    if (!TEST_true(SSL_CTX_set_ciphersuites(cctx,
                                            "TLS_CHACHA20_POLY1305_SHA256"))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl, clntsess))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE))
            || !TEST_true(SSL_session_reused(clientssl)))
        goto end;

    SSL_SESSION_free(clntsess);
    clntsess = SSL_get1_session(clientssl);
    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;
# endif

    /*
     * Check attempting to resume a SHA-256 session with no SHA-256 ciphersuites
     * succeeds but does not resume.
     */
    if (!TEST_true(SSL_CTX_set_ciphersuites(cctx, "TLS_AES_256_GCM_SHA384"))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl, clntsess))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_SSL))
            || !TEST_false(SSL_session_reused(clientssl)))
        goto end;

    SSL_SESSION_free(clntsess);
    clntsess = NULL;
    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;

    /* Create a session based on SHA384 */
    if (!TEST_true(SSL_CTX_set_ciphersuites(cctx, "TLS_AES_256_GCM_SHA384"))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl,
                                          &clientssl, NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    clntsess = SSL_get1_session(clientssl);
    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;

    if (!TEST_true(SSL_CTX_set_ciphersuites(cctx,
                   "TLS_AES_128_GCM_SHA256:TLS_AES_256_GCM_SHA384"))
            || !TEST_true(SSL_CTX_set_ciphersuites(sctx,
                                                   "TLS_AES_256_GCM_SHA384"))
            || !TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(SSL_set_session(clientssl, clntsess))
               /*
                * We use SSL_ERROR_WANT_READ below so that we can pause the
                * connection after the initial ClientHello has been sent to
                * enable us to make some session changes.
                */
            || !TEST_false(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_WANT_READ)))
        goto end;

    /* Trick the client into thinking this session is for a different digest */
    clntsess->cipher = aes_128_gcm_sha256;
    clntsess->cipher_id = clntsess->cipher->id;

    /*
     * Continue the previously started connection. Server has selected a SHA-384
     * ciphersuite, but client thinks the session is for SHA-256, so it should
     * bail out.
     */
    if (!TEST_false(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_SSL))
            || !TEST_int_eq(ERR_GET_REASON(ERR_get_error()),
                            SSL_R_CIPHERSUITE_DIGEST_HAS_CHANGED))
        goto end;

    testresult = 1;

 end:
    SSL_SESSION_free(clntsess);
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);

    return testresult;
}