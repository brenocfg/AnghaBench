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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * SSL_CIPHER_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int SSL_CTX_set_ciphersuites (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_client_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_find_session_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_server_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_psk_use_session_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_SESSION_new () ; 
 int SSL_SESSION_set1_master_key (int /*<<< orphan*/  const*,unsigned char const*,int) ; 
 int SSL_SESSION_set_cipher (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int SSL_SESSION_set_protocol_version (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int SSL_SESSION_up_ref (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int SSL_session_reused (int /*<<< orphan*/ *) ; 
 int SSL_set1_groups_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  TLS13_AES_128_GCM_SHA256_BYTES ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/ * cert ; 
 int /*<<< orphan*/  const* clientpsk ; 
 int create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_session_cb ; 
 int find_session_cb_cnt ; 
 int /*<<< orphan*/ * privkey ; 
 int /*<<< orphan*/  psk_client_cb ; 
 int psk_client_cb_cnt ; 
 int /*<<< orphan*/  psk_server_cb ; 
 int psk_server_cb_cnt ; 
 char* pskid ; 
 int /*<<< orphan*/  const* serverpsk ; 
 int /*<<< orphan*/  shutdown_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* srvid ; 
 int /*<<< orphan*/  use_session_cb ; 
 int use_session_cb_cnt ; 

__attribute__((used)) static int test_tls13_psk(int idx)
{
    SSL_CTX *sctx = NULL, *cctx = NULL;
    SSL *serverssl = NULL, *clientssl = NULL;
    const SSL_CIPHER *cipher = NULL;
    const unsigned char key[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
        0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
    };
    int testresult = 0;

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(), TLS_client_method(),
                                       TLS1_VERSION, 0,
                                       &sctx, &cctx, idx == 3 ? NULL : cert,
                                       idx == 3 ? NULL : privkey)))
        goto end;

    if (idx != 3) {
        /*
         * We use a ciphersuite with SHA256 to ease testing old style PSK
         * callbacks which will always default to SHA256. This should not be
         * necessary if we have no cert/priv key. In that case the server should
         * prefer SHA256 automatically.
         */
        if (!TEST_true(SSL_CTX_set_ciphersuites(cctx,
                                                "TLS_AES_128_GCM_SHA256")))
            goto end;
    }

    /*
     * Test 0: New style callbacks only
     * Test 1: New and old style callbacks (only the new ones should be used)
     * Test 2: Old style callbacks only
     */
    if (idx == 0 || idx == 1) {
        SSL_CTX_set_psk_use_session_callback(cctx, use_session_cb);
        SSL_CTX_set_psk_find_session_callback(sctx, find_session_cb);
    }
#ifndef OPENSSL_NO_PSK
    if (idx >= 1) {
        SSL_CTX_set_psk_client_callback(cctx, psk_client_cb);
        SSL_CTX_set_psk_server_callback(sctx, psk_server_cb);
    }
#endif
    srvid = pskid;
    use_session_cb_cnt = 0;
    find_session_cb_cnt = 0;
    psk_client_cb_cnt = 0;
    psk_server_cb_cnt = 0;

    if (idx != 3) {
        /*
         * Check we can create a connection if callback decides not to send a
         * PSK
         */
        if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                                 NULL, NULL))
                || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                    SSL_ERROR_NONE))
                || !TEST_false(SSL_session_reused(clientssl))
                || !TEST_false(SSL_session_reused(serverssl)))
            goto end;

        if (idx == 0 || idx == 1) {
            if (!TEST_true(use_session_cb_cnt == 1)
                    || !TEST_true(find_session_cb_cnt == 0)
                       /*
                        * If no old style callback then below should be 0
                        * otherwise 1
                        */
                    || !TEST_true(psk_client_cb_cnt == idx)
                    || !TEST_true(psk_server_cb_cnt == 0))
                goto end;
        } else {
            if (!TEST_true(use_session_cb_cnt == 0)
                    || !TEST_true(find_session_cb_cnt == 0)
                    || !TEST_true(psk_client_cb_cnt == 1)
                    || !TEST_true(psk_server_cb_cnt == 0))
                goto end;
        }

        shutdown_ssl_connection(serverssl, clientssl);
        serverssl = clientssl = NULL;
        use_session_cb_cnt = psk_client_cb_cnt = 0;
    }

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL)))
        goto end;

    /* Create the PSK */
    cipher = SSL_CIPHER_find(clientssl, TLS13_AES_128_GCM_SHA256_BYTES);
    clientpsk = SSL_SESSION_new();
    if (!TEST_ptr(clientpsk)
            || !TEST_ptr(cipher)
            || !TEST_true(SSL_SESSION_set1_master_key(clientpsk, key,
                                                      sizeof(key)))
            || !TEST_true(SSL_SESSION_set_cipher(clientpsk, cipher))
            || !TEST_true(SSL_SESSION_set_protocol_version(clientpsk,
                                                           TLS1_3_VERSION))
            || !TEST_true(SSL_SESSION_up_ref(clientpsk)))
        goto end;
    serverpsk = clientpsk;

    /* Check we can create a connection and the PSK is used */
    if (!TEST_true(create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE))
            || !TEST_true(SSL_session_reused(clientssl))
            || !TEST_true(SSL_session_reused(serverssl)))
        goto end;

    if (idx == 0 || idx == 1) {
        if (!TEST_true(use_session_cb_cnt == 1)
                || !TEST_true(find_session_cb_cnt == 1)
                || !TEST_true(psk_client_cb_cnt == 0)
                || !TEST_true(psk_server_cb_cnt == 0))
            goto end;
    } else {
        if (!TEST_true(use_session_cb_cnt == 0)
                || !TEST_true(find_session_cb_cnt == 0)
                || !TEST_true(psk_client_cb_cnt == 1)
                || !TEST_true(psk_server_cb_cnt == 1))
            goto end;
    }

    shutdown_ssl_connection(serverssl, clientssl);
    serverssl = clientssl = NULL;
    use_session_cb_cnt = find_session_cb_cnt = 0;
    psk_client_cb_cnt = psk_server_cb_cnt = 0;

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL)))
        goto end;

    /* Force an HRR */
#if defined(OPENSSL_NO_EC)
    if (!TEST_true(SSL_set1_groups_list(serverssl, "ffdhe3072")))
        goto end;
#else
    if (!TEST_true(SSL_set1_groups_list(serverssl, "P-256")))
        goto end;
#endif

    /*
     * Check we can create a connection, the PSK is used and the callbacks are
     * called twice.
     */
    if (!TEST_true(create_ssl_connection(serverssl, clientssl, SSL_ERROR_NONE))
            || !TEST_true(SSL_session_reused(clientssl))
            || !TEST_true(SSL_session_reused(serverssl)))
        goto end;

    if (idx == 0 || idx == 1) {
        if (!TEST_true(use_session_cb_cnt == 2)
                || !TEST_true(find_session_cb_cnt == 2)
                || !TEST_true(psk_client_cb_cnt == 0)
                || !TEST_true(psk_server_cb_cnt == 0))
            goto end;
    } else {
        if (!TEST_true(use_session_cb_cnt == 0)
                || !TEST_true(find_session_cb_cnt == 0)
                || !TEST_true(psk_client_cb_cnt == 2)
                || !TEST_true(psk_server_cb_cnt == 2))
            goto end;
    }

    shutdown_ssl_connection(serverssl, clientssl);
    serverssl = clientssl = NULL;
    use_session_cb_cnt = find_session_cb_cnt = 0;
    psk_client_cb_cnt = psk_server_cb_cnt = 0;

    if (idx != 3) {
        /*
         * Check that if the server rejects the PSK we can still connect, but with
         * a full handshake
         */
        srvid = "Dummy Identity";
        if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                                 NULL, NULL))
                || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                    SSL_ERROR_NONE))
                || !TEST_false(SSL_session_reused(clientssl))
                || !TEST_false(SSL_session_reused(serverssl)))
            goto end;

        if (idx == 0 || idx == 1) {
            if (!TEST_true(use_session_cb_cnt == 1)
                    || !TEST_true(find_session_cb_cnt == 1)
                    || !TEST_true(psk_client_cb_cnt == 0)
                       /*
                        * If no old style callback then below should be 0
                        * otherwise 1
                        */
                    || !TEST_true(psk_server_cb_cnt == idx))
                goto end;
        } else {
            if (!TEST_true(use_session_cb_cnt == 0)
                    || !TEST_true(find_session_cb_cnt == 0)
                    || !TEST_true(psk_client_cb_cnt == 1)
                    || !TEST_true(psk_server_cb_cnt == 1))
                goto end;
        }

        shutdown_ssl_connection(serverssl, clientssl);
        serverssl = clientssl = NULL;
    }
    testresult = 1;

 end:
    SSL_SESSION_free(clientpsk);
    SSL_SESSION_free(serverpsk);
    clientpsk = serverpsk = NULL;
    SSL_free(serverssl);
    SSL_free(clientssl);
    SSL_CTX_free(sctx);
    SSL_CTX_free(cctx);
    return testresult;
}