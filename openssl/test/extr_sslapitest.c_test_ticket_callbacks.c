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
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_cache_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_ticket_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_ticket_key_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_ERROR_NONE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESS_CACHE_OFF ; 
 scalar_t__ SSL_TICKET_RETURN_ABORT ; 
 scalar_t__ SSL_TICKET_RETURN_IGNORE ; 
 scalar_t__ SSL_TICKET_RETURN_IGNORE_RENEW ; 
 scalar_t__ SSL_TICKET_RETURN_USE ; 
 scalar_t__ SSL_TICKET_RETURN_USE_RENEW ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_session_reused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (scalar_t__,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  create_ssl_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_ctx_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ssl_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dec_tick_called ; 
 int /*<<< orphan*/  dec_tick_cb ; 
 scalar_t__ gen_tick_called ; 
 int /*<<< orphan*/  gen_tick_cb ; 
 int /*<<< orphan*/  privkey ; 
 scalar_t__ tick_dec_ret ; 
 int /*<<< orphan*/  tick_key_cb ; 
 scalar_t__ tick_key_cb_called ; 
 int tick_key_renew ; 

__attribute__((used)) static int test_ticket_callbacks(int tst)
{
    SSL_CTX *cctx = NULL, *sctx = NULL;
    SSL *clientssl = NULL, *serverssl = NULL;
    SSL_SESSION *clntsess = NULL;
    int testresult = 0;

#ifdef OPENSSL_NO_TLS1_2
    if (tst % 2 == 0)
        return 1;
#endif
#ifdef OPENSSL_NO_TLS1_3
    if (tst % 2 == 1)
        return 1;
#endif

    gen_tick_called = dec_tick_called = tick_key_cb_called = 0;

    /* Which tests the ticket key callback should request renewal for */
    if (tst == 10 || tst == 11)
        tick_key_renew = 1;
    else
        tick_key_renew = 0;

    /* Which tests the decrypt ticket callback should request renewal for */
    switch (tst) {
    case 0:
    case 1:
        tick_dec_ret = SSL_TICKET_RETURN_IGNORE;
        break;

    case 2:
    case 3:
        tick_dec_ret = SSL_TICKET_RETURN_IGNORE_RENEW;
        break;

    case 4:
    case 5:
        tick_dec_ret = SSL_TICKET_RETURN_USE;
        break;

    case 6:
    case 7:
        tick_dec_ret = SSL_TICKET_RETURN_USE_RENEW;
        break;

    default:
        tick_dec_ret = SSL_TICKET_RETURN_ABORT;
    }

    if (!TEST_true(create_ssl_ctx_pair(TLS_server_method(),
                                       TLS_client_method(),
                                       TLS1_VERSION,
                                       ((tst % 2) == 0) ? TLS1_2_VERSION
                                                        : TLS1_3_VERSION,
                                       &sctx, &cctx, cert, privkey)))
        goto end;

    /*
     * We only want sessions to resume from tickets - not the session cache. So
     * switch the cache off.
     */
    if (!TEST_true(SSL_CTX_set_session_cache_mode(sctx, SSL_SESS_CACHE_OFF)))
        goto end;

    if (!TEST_true(SSL_CTX_set_session_ticket_cb(sctx, gen_tick_cb, dec_tick_cb,
                                                 NULL)))
        goto end;

    if (tst >= 8
            && !TEST_true(SSL_CTX_set_tlsext_ticket_key_cb(sctx, tick_key_cb)))
        goto end;

    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl,
                                             NULL, NULL))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    /*
     * The decrypt ticket key callback in TLSv1.2 should be called even though
     * we have no ticket yet, because it gets called with a status of
     * SSL_TICKET_EMPTY (the client indicates support for tickets but does not
     * actually send any ticket data). This does not happen in TLSv1.3 because
     * it is not valid to send empty ticket data in TLSv1.3.
     */
    if (!TEST_int_eq(gen_tick_called, 1)
            || !TEST_int_eq(dec_tick_called, ((tst % 2) == 0) ? 1 : 0))
        goto end;

    gen_tick_called = dec_tick_called = 0;

    clntsess = SSL_get1_session(clientssl);
    SSL_shutdown(clientssl);
    SSL_shutdown(serverssl);
    SSL_free(serverssl);
    SSL_free(clientssl);
    serverssl = clientssl = NULL;

    /* Now do a resumption */
    if (!TEST_true(create_ssl_objects(sctx, cctx, &serverssl, &clientssl, NULL,
                                      NULL))
            || !TEST_true(SSL_set_session(clientssl, clntsess))
            || !TEST_true(create_ssl_connection(serverssl, clientssl,
                                                SSL_ERROR_NONE)))
        goto end;

    if (tick_dec_ret == SSL_TICKET_RETURN_IGNORE
            || tick_dec_ret == SSL_TICKET_RETURN_IGNORE_RENEW) {
        if (!TEST_false(SSL_session_reused(clientssl)))
            goto end;
    } else {
        if (!TEST_true(SSL_session_reused(clientssl)))
            goto end;
    }

    if (!TEST_int_eq(gen_tick_called,
                     (tick_key_renew
                      || tick_dec_ret == SSL_TICKET_RETURN_IGNORE_RENEW
                      || tick_dec_ret == SSL_TICKET_RETURN_USE_RENEW)
                     ? 1 : 0)
            || !TEST_int_eq(dec_tick_called, 1))
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