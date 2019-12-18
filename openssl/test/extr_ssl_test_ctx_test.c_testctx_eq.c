#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  session_id_expected; int /*<<< orphan*/  resumption_expected; int /*<<< orphan*/  expected_session_ticket_app_data; int /*<<< orphan*/  expected_cipher; int /*<<< orphan*/  expected_alpn_protocol; int /*<<< orphan*/  expected_npn_protocol; int /*<<< orphan*/  compression_expected; int /*<<< orphan*/  session_ticket_expected; int /*<<< orphan*/  expected_servername; int /*<<< orphan*/  expected_protocol; int /*<<< orphan*/  expected_server_alert; int /*<<< orphan*/  expected_client_alert; int /*<<< orphan*/  expected_result; int /*<<< orphan*/  resume_extra; int /*<<< orphan*/  extra; int /*<<< orphan*/  max_fragment_size; int /*<<< orphan*/  app_data_size; int /*<<< orphan*/  handshake_mode; int /*<<< orphan*/  method; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extraconf_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int testctx_eq(SSL_TEST_CTX *ctx, SSL_TEST_CTX *ctx2)
{
    if (!TEST_int_eq(ctx->method, ctx2->method)
            || !TEST_int_eq(ctx->handshake_mode, ctx2->handshake_mode)
            || !TEST_int_eq(ctx->app_data_size, ctx2->app_data_size)
            || !TEST_int_eq(ctx->max_fragment_size, ctx2->max_fragment_size)
            || !extraconf_eq(&ctx->extra, &ctx2->extra)
            || !extraconf_eq(&ctx->resume_extra, &ctx2->resume_extra)
            || !TEST_int_eq(ctx->expected_result, ctx2->expected_result)
            || !TEST_int_eq(ctx->expected_client_alert,
                            ctx2->expected_client_alert)
            || !TEST_int_eq(ctx->expected_server_alert,
                            ctx2->expected_server_alert)
            || !TEST_int_eq(ctx->expected_protocol, ctx2->expected_protocol)
            || !TEST_int_eq(ctx->expected_servername, ctx2->expected_servername)
            || !TEST_int_eq(ctx->session_ticket_expected,
                            ctx2->session_ticket_expected)
            || !TEST_int_eq(ctx->compression_expected,
                            ctx2->compression_expected)
            || !TEST_str_eq(ctx->expected_npn_protocol,
                            ctx2->expected_npn_protocol)
            || !TEST_str_eq(ctx->expected_alpn_protocol,
                            ctx2->expected_alpn_protocol)
            || !TEST_str_eq(ctx->expected_cipher,
                            ctx2->expected_cipher)
            || !TEST_str_eq(ctx->expected_session_ticket_app_data,
                            ctx2->expected_session_ticket_app_data)
            || !TEST_int_eq(ctx->resumption_expected,
                            ctx2->resumption_expected)
            || !TEST_int_eq(ctx->session_id_expected,
                            ctx2->session_id_expected))
        return 0;
    return 1;
}