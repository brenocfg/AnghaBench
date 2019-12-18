#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {unsigned char* npn_protocols; size_t npn_protocols_len; unsigned char* alpn_protocols; size_t alpn_protocols_len; void* srp_password; void* srp_user; void* session_ticket_app_data; } ;
struct TYPE_21__ {int /*<<< orphan*/  max_fragment_size; } ;
struct TYPE_19__ {int verify_callback; int max_fragment_len_mode; int ct_validation; int /*<<< orphan*/ * srp_password; int /*<<< orphan*/ * srp_user; int /*<<< orphan*/ * alpn_protocols; int /*<<< orphan*/ * npn_protocols; } ;
struct TYPE_18__ {int /*<<< orphan*/ * srp_password; int /*<<< orphan*/ * srp_user; int /*<<< orphan*/ * session_ticket_app_data; int /*<<< orphan*/ * alpn_protocols; int /*<<< orphan*/ * npn_protocols; } ;
struct TYPE_17__ {int servername_callback; scalar_t__ cert_status; int /*<<< orphan*/ * srp_password; int /*<<< orphan*/ * srp_user; int /*<<< orphan*/ * session_ticket_app_data; int /*<<< orphan*/ * alpn_protocols; int /*<<< orphan*/ * npn_protocols; scalar_t__ broken_session_ticket; } ;
struct TYPE_20__ {TYPE_3__ client; TYPE_2__ server2; TYPE_1__ server; } ;
typedef  TYPE_4__ SSL_TEST_EXTRA_CONF ;
typedef  TYPE_5__ SSL_TEST_CTX ;
typedef  unsigned char SSL_CTX ;
typedef  TYPE_6__ CTX_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 void* OPENSSL_strdup (int /*<<< orphan*/ *) ; 
 unsigned char* OPENSSL_zalloc (size_t) ; 
 int /*<<< orphan*/  SSL_CTX_enable_ct (unsigned char*,int /*<<< orphan*/ ) ; 
 size_t SSL_CTX_set_alpn_protos (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  SSL_CTX_set_alpn_select_cb (unsigned char*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_cert_verify_callback (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_client_hello_cb (unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_default_ctlog_list_file (unsigned char*) ; 
 size_t SSL_CTX_set_max_send_fragment (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_next_proto_select_cb (unsigned char*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_npn_advertised_cb (unsigned char*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_ticket_cb (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_srp_cb_arg (unsigned char*,TYPE_6__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_srp_client_pwd_callback (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_srp_username (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_srp_username_callback (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_max_fragment_length (unsigned char*,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_servername_arg (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_servername_callback (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_status_arg (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_status_cb (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_status_type (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_tlsext_ticket_key_cb (unsigned char*,int /*<<< orphan*/ ) ; 
 size_t SSL_CTX_set_tlsext_ticket_keys (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  SSL_CT_VALIDATION_PERMISSIVE ; 
 int /*<<< orphan*/  SSL_CT_VALIDATION_STRICT ; 
 scalar_t__ SSL_TEST_CERT_STATUS_GOOD_RESPONSE ; 
 scalar_t__ SSL_TEST_CERT_STATUS_NONE ; 
#define  SSL_TEST_CT_VALIDATION_NONE 144 
#define  SSL_TEST_CT_VALIDATION_PERMISSIVE 143 
#define  SSL_TEST_CT_VALIDATION_STRICT 142 
#define  SSL_TEST_SERVERNAME_CB_NONE 141 
#define  SSL_TEST_SERVERNAME_CLIENT_HELLO_IGNORE_MISMATCH 140 
#define  SSL_TEST_SERVERNAME_CLIENT_HELLO_NO_V12 139 
#define  SSL_TEST_SERVERNAME_CLIENT_HELLO_REJECT_MISMATCH 138 
#define  SSL_TEST_SERVERNAME_IGNORE_MISMATCH 137 
#define  SSL_TEST_SERVERNAME_REJECT_MISMATCH 136 
#define  SSL_TEST_VERIFY_ACCEPT_ALL 135 
#define  SSL_TEST_VERIFY_NONE 134 
#define  SSL_TEST_VERIFY_REJECT_ALL 133 
 int /*<<< orphan*/  TEST_int_eq (size_t,int) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_STATUSTYPE_ocsp ; 
#define  TLSEXT_max_fragment_length_1024 132 
#define  TLSEXT_max_fragment_length_2048 131 
#define  TLSEXT_max_fragment_length_4096 130 
#define  TLSEXT_max_fragment_length_512 129 
#define  TLSEXT_max_fragment_length_DISABLED 128 
 int /*<<< orphan*/  broken_session_ticket_cb ; 
 int /*<<< orphan*/  client_hello_ignore_cb ; 
 int /*<<< orphan*/  client_hello_nov12_cb ; 
 int /*<<< orphan*/  client_hello_reject_cb ; 
 int /*<<< orphan*/  client_npn_cb ; 
 int /*<<< orphan*/  client_ocsp_cb ; 
 int /*<<< orphan*/  client_srp_cb ; 
 int /*<<< orphan*/  decrypt_session_ticket_cb ; 
 int /*<<< orphan*/  do_not_call_session_ticket_cb ; 
 int /*<<< orphan*/  dummy_ocsp_resp_bad_val ; 
 int /*<<< orphan*/  dummy_ocsp_resp_good_val ; 
 int /*<<< orphan*/ * generate_session_ticket_cb ; 
 int /*<<< orphan*/  parse_protos (int /*<<< orphan*/ *,unsigned char**,size_t*) ; 
 int /*<<< orphan*/  server_alpn_cb ; 
 int /*<<< orphan*/  server_npn_cb ; 
 int /*<<< orphan*/  server_ocsp_cb ; 
 int /*<<< orphan*/  server_srp_cb ; 
 int /*<<< orphan*/  servername_ignore_cb ; 
 int /*<<< orphan*/  servername_reject_cb ; 
 int /*<<< orphan*/  verify_accept_cb ; 
 int /*<<< orphan*/  verify_reject_cb ; 

__attribute__((used)) static int configure_handshake_ctx(SSL_CTX *server_ctx, SSL_CTX *server2_ctx,
                                   SSL_CTX *client_ctx,
                                   const SSL_TEST_CTX *test,
                                   const SSL_TEST_EXTRA_CONF *extra,
                                   CTX_DATA *server_ctx_data,
                                   CTX_DATA *server2_ctx_data,
                                   CTX_DATA *client_ctx_data)
{
    unsigned char *ticket_keys;
    size_t ticket_key_len;

    if (!TEST_int_eq(SSL_CTX_set_max_send_fragment(server_ctx,
                                                   test->max_fragment_size), 1))
        goto err;
    if (server2_ctx != NULL) {
        if (!TEST_int_eq(SSL_CTX_set_max_send_fragment(server2_ctx,
                                                       test->max_fragment_size),
                         1))
            goto err;
    }
    if (!TEST_int_eq(SSL_CTX_set_max_send_fragment(client_ctx,
                                                   test->max_fragment_size), 1))
        goto err;

    switch (extra->client.verify_callback) {
    case SSL_TEST_VERIFY_ACCEPT_ALL:
        SSL_CTX_set_cert_verify_callback(client_ctx, &verify_accept_cb, NULL);
        break;
    case SSL_TEST_VERIFY_REJECT_ALL:
        SSL_CTX_set_cert_verify_callback(client_ctx, &verify_reject_cb, NULL);
        break;
    case SSL_TEST_VERIFY_NONE:
        break;
    }

    switch (extra->client.max_fragment_len_mode) {
    case TLSEXT_max_fragment_length_512:
    case TLSEXT_max_fragment_length_1024:
    case TLSEXT_max_fragment_length_2048:
    case TLSEXT_max_fragment_length_4096:
    case TLSEXT_max_fragment_length_DISABLED:
        SSL_CTX_set_tlsext_max_fragment_length(
              client_ctx, extra->client.max_fragment_len_mode);
        break;
    }

    /*
     * Link the two contexts for SNI purposes.
     * Also do ClientHello callbacks here, as setting both ClientHello and SNI
     * is bad.
     */
    switch (extra->server.servername_callback) {
    case SSL_TEST_SERVERNAME_IGNORE_MISMATCH:
        SSL_CTX_set_tlsext_servername_callback(server_ctx, servername_ignore_cb);
        SSL_CTX_set_tlsext_servername_arg(server_ctx, server2_ctx);
        break;
    case SSL_TEST_SERVERNAME_REJECT_MISMATCH:
        SSL_CTX_set_tlsext_servername_callback(server_ctx, servername_reject_cb);
        SSL_CTX_set_tlsext_servername_arg(server_ctx, server2_ctx);
        break;
    case SSL_TEST_SERVERNAME_CB_NONE:
        break;
    case SSL_TEST_SERVERNAME_CLIENT_HELLO_IGNORE_MISMATCH:
        SSL_CTX_set_client_hello_cb(server_ctx, client_hello_ignore_cb, server2_ctx);
        break;
    case SSL_TEST_SERVERNAME_CLIENT_HELLO_REJECT_MISMATCH:
        SSL_CTX_set_client_hello_cb(server_ctx, client_hello_reject_cb, server2_ctx);
        break;
    case SSL_TEST_SERVERNAME_CLIENT_HELLO_NO_V12:
        SSL_CTX_set_client_hello_cb(server_ctx, client_hello_nov12_cb, server2_ctx);
    }

    if (extra->server.cert_status != SSL_TEST_CERT_STATUS_NONE) {
        SSL_CTX_set_tlsext_status_type(client_ctx, TLSEXT_STATUSTYPE_ocsp);
        SSL_CTX_set_tlsext_status_cb(client_ctx, client_ocsp_cb);
        SSL_CTX_set_tlsext_status_arg(client_ctx, NULL);
        SSL_CTX_set_tlsext_status_cb(server_ctx, server_ocsp_cb);
        SSL_CTX_set_tlsext_status_arg(server_ctx,
            ((extra->server.cert_status == SSL_TEST_CERT_STATUS_GOOD_RESPONSE)
            ? &dummy_ocsp_resp_good_val : &dummy_ocsp_resp_bad_val));
    }

    /*
     * The initial_ctx/session_ctx always handles the encrypt/decrypt of the
     * session ticket. This ticket_key callback is assigned to the second
     * session (assigned via SNI), and should never be invoked
     */
    if (server2_ctx != NULL)
        SSL_CTX_set_tlsext_ticket_key_cb(server2_ctx,
                                         do_not_call_session_ticket_cb);

    if (extra->server.broken_session_ticket) {
        SSL_CTX_set_tlsext_ticket_key_cb(server_ctx, broken_session_ticket_cb);
    }
#ifndef OPENSSL_NO_NEXTPROTONEG
    if (extra->server.npn_protocols != NULL) {
        if (!TEST_true(parse_protos(extra->server.npn_protocols,
                                    &server_ctx_data->npn_protocols,
                                    &server_ctx_data->npn_protocols_len)))
            goto err;
        SSL_CTX_set_npn_advertised_cb(server_ctx, server_npn_cb,
                                      server_ctx_data);
    }
    if (extra->server2.npn_protocols != NULL) {
        if (!TEST_true(parse_protos(extra->server2.npn_protocols,
                                    &server2_ctx_data->npn_protocols,
                                    &server2_ctx_data->npn_protocols_len))
                || !TEST_ptr(server2_ctx))
            goto err;
        SSL_CTX_set_npn_advertised_cb(server2_ctx, server_npn_cb,
                                      server2_ctx_data);
    }
    if (extra->client.npn_protocols != NULL) {
        if (!TEST_true(parse_protos(extra->client.npn_protocols,
                                    &client_ctx_data->npn_protocols,
                                    &client_ctx_data->npn_protocols_len)))
            goto err;
        SSL_CTX_set_next_proto_select_cb(client_ctx, client_npn_cb,
                                         client_ctx_data);
    }
#endif
    if (extra->server.alpn_protocols != NULL) {
        if (!TEST_true(parse_protos(extra->server.alpn_protocols,
                                    &server_ctx_data->alpn_protocols,
                                    &server_ctx_data->alpn_protocols_len)))
            goto err;
        SSL_CTX_set_alpn_select_cb(server_ctx, server_alpn_cb, server_ctx_data);
    }
    if (extra->server2.alpn_protocols != NULL) {
        if (!TEST_ptr(server2_ctx)
                || !TEST_true(parse_protos(extra->server2.alpn_protocols,
                                           &server2_ctx_data->alpn_protocols,
                                           &server2_ctx_data->alpn_protocols_len
            )))
            goto err;
        SSL_CTX_set_alpn_select_cb(server2_ctx, server_alpn_cb,
                                   server2_ctx_data);
    }
    if (extra->client.alpn_protocols != NULL) {
        unsigned char *alpn_protos = NULL;
        size_t alpn_protos_len;
        if (!TEST_true(parse_protos(extra->client.alpn_protocols,
                                    &alpn_protos, &alpn_protos_len))
                /* Reversed return value convention... */
                || !TEST_int_eq(SSL_CTX_set_alpn_protos(client_ctx, alpn_protos,
                                                        alpn_protos_len), 0))
            goto err;
        OPENSSL_free(alpn_protos);
    }

    if (extra->server.session_ticket_app_data != NULL) {
        server_ctx_data->session_ticket_app_data =
            OPENSSL_strdup(extra->server.session_ticket_app_data);
        SSL_CTX_set_session_ticket_cb(server_ctx, generate_session_ticket_cb,
                                      decrypt_session_ticket_cb, server_ctx_data);
    }
    if (extra->server2.session_ticket_app_data != NULL) {
        if (!TEST_ptr(server2_ctx))
            goto err;
        server2_ctx_data->session_ticket_app_data =
            OPENSSL_strdup(extra->server2.session_ticket_app_data);
        SSL_CTX_set_session_ticket_cb(server2_ctx, NULL,
                                      decrypt_session_ticket_cb, server2_ctx_data);
    }

    /*
     * Use fixed session ticket keys so that we can decrypt a ticket created with
     * one CTX in another CTX. Don't address server2 for the moment.
     */
    ticket_key_len = SSL_CTX_set_tlsext_ticket_keys(server_ctx, NULL, 0);
    if (!TEST_ptr(ticket_keys = OPENSSL_zalloc(ticket_key_len))
            || !TEST_int_eq(SSL_CTX_set_tlsext_ticket_keys(server_ctx,
                                                           ticket_keys,
                                                           ticket_key_len), 1)) {
        OPENSSL_free(ticket_keys);
        goto err;
    }
    OPENSSL_free(ticket_keys);

    /* The default log list includes EC keys, so CT can't work without EC. */
#if !defined(OPENSSL_NO_CT) && !defined(OPENSSL_NO_EC)
    if (!TEST_true(SSL_CTX_set_default_ctlog_list_file(client_ctx)))
        goto err;
    switch (extra->client.ct_validation) {
    case SSL_TEST_CT_VALIDATION_PERMISSIVE:
        if (!TEST_true(SSL_CTX_enable_ct(client_ctx,
                                         SSL_CT_VALIDATION_PERMISSIVE)))
            goto err;
        break;
    case SSL_TEST_CT_VALIDATION_STRICT:
        if (!TEST_true(SSL_CTX_enable_ct(client_ctx, SSL_CT_VALIDATION_STRICT)))
            goto err;
        break;
    case SSL_TEST_CT_VALIDATION_NONE:
        break;
    }
#endif
#ifndef OPENSSL_NO_SRP
    if (extra->server.srp_user != NULL) {
        SSL_CTX_set_srp_username_callback(server_ctx, server_srp_cb);
        server_ctx_data->srp_user = OPENSSL_strdup(extra->server.srp_user);
        server_ctx_data->srp_password = OPENSSL_strdup(extra->server.srp_password);
        SSL_CTX_set_srp_cb_arg(server_ctx, server_ctx_data);
    }
    if (extra->server2.srp_user != NULL) {
        if (!TEST_ptr(server2_ctx))
            goto err;
        SSL_CTX_set_srp_username_callback(server2_ctx, server_srp_cb);
        server2_ctx_data->srp_user = OPENSSL_strdup(extra->server2.srp_user);
        server2_ctx_data->srp_password = OPENSSL_strdup(extra->server2.srp_password);
        SSL_CTX_set_srp_cb_arg(server2_ctx, server2_ctx_data);
    }
    if (extra->client.srp_user != NULL) {
        if (!TEST_true(SSL_CTX_set_srp_username(client_ctx,
                                                extra->client.srp_user)))
            goto err;
        SSL_CTX_set_srp_client_pwd_callback(client_ctx, client_srp_cb);
        client_ctx_data->srp_password = OPENSSL_strdup(extra->client.srp_password);
        SSL_CTX_set_srp_cb_arg(client_ctx, client_ctx_data);
    }
#endif  /* !OPENSSL_NO_SRP */
    return 1;
err:
    return 0;
}