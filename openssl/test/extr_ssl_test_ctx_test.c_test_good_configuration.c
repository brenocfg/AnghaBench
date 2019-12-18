#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {char* test_section; TYPE_7__* expected_ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  ct_validation; } ;
struct TYPE_13__ {void* alpn_protocols; } ;
struct TYPE_15__ {TYPE_5__ client; TYPE_4__ server2; } ;
struct TYPE_11__ {int broken_session_ticket; int /*<<< orphan*/  servername_callback; } ;
struct TYPE_10__ {scalar_t__ max_fragment_len_mode; void* npn_protocols; void* servername; int /*<<< orphan*/  verify_callback; } ;
struct TYPE_12__ {TYPE_2__ server; TYPE_1__ client; } ;
struct TYPE_16__ {int app_data_size; int max_fragment_size; int resumption_expected; TYPE_6__ resume_extra; TYPE_3__ extra; int /*<<< orphan*/  session_id_expected; int /*<<< orphan*/  compression_expected; int /*<<< orphan*/  session_ticket_expected; void* expected_servername; int /*<<< orphan*/  expected_protocol; scalar_t__ expected_server_alert; int /*<<< orphan*/  expected_client_alert; int /*<<< orphan*/  expected_result; int /*<<< orphan*/  handshake_mode; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECUTE_SSL_TEST_CTX_TEST () ; 
 void* OPENSSL_strdup (char*) ; 
 int /*<<< orphan*/  SETUP_SSL_TEST_CTX_TEST_FIXTURE () ; 
 int /*<<< orphan*/  SSL_AD_UNKNOWN_CA ; 
 int /*<<< orphan*/  SSL_TEST_COMPRESSION_NO ; 
 int /*<<< orphan*/  SSL_TEST_CT_VALIDATION_STRICT ; 
 int /*<<< orphan*/  SSL_TEST_HANDSHAKE_RESUME ; 
 int /*<<< orphan*/  SSL_TEST_METHOD_DTLS ; 
 int /*<<< orphan*/  SSL_TEST_SERVERNAME_IGNORE_MISMATCH ; 
 void* SSL_TEST_SERVERNAME_SERVER2 ; 
 int /*<<< orphan*/  SSL_TEST_SERVER_FAIL ; 
 int /*<<< orphan*/  SSL_TEST_SESSION_ID_IGNORE ; 
 int /*<<< orphan*/  SSL_TEST_SESSION_TICKET_YES ; 
 int /*<<< orphan*/  SSL_TEST_VERIFY_REJECT_ALL ; 
 int /*<<< orphan*/  TEST_ptr (void*) ; 
 int /*<<< orphan*/  TLS1_1_VERSION ; 
 TYPE_8__* fixture ; 
 int result ; 
 int /*<<< orphan*/  tear_down (TYPE_8__*) ; 

__attribute__((used)) static int test_good_configuration(void)
{
    SETUP_SSL_TEST_CTX_TEST_FIXTURE();
    if (fixture == NULL)
        return 0;
    fixture->test_section = "ssltest_good";
    fixture->expected_ctx->method = SSL_TEST_METHOD_DTLS;
    fixture->expected_ctx->handshake_mode = SSL_TEST_HANDSHAKE_RESUME;
    fixture->expected_ctx->app_data_size = 1024;
    fixture->expected_ctx->max_fragment_size = 2048;

    fixture->expected_ctx->expected_result = SSL_TEST_SERVER_FAIL;
    fixture->expected_ctx->expected_client_alert = SSL_AD_UNKNOWN_CA;
    fixture->expected_ctx->expected_server_alert = 0;  /* No alert. */
    fixture->expected_ctx->expected_protocol = TLS1_1_VERSION;
    fixture->expected_ctx->expected_servername = SSL_TEST_SERVERNAME_SERVER2;
    fixture->expected_ctx->session_ticket_expected = SSL_TEST_SESSION_TICKET_YES;
    fixture->expected_ctx->compression_expected = SSL_TEST_COMPRESSION_NO;
    fixture->expected_ctx->session_id_expected = SSL_TEST_SESSION_ID_IGNORE;
    fixture->expected_ctx->resumption_expected = 1;

    fixture->expected_ctx->extra.client.verify_callback =
        SSL_TEST_VERIFY_REJECT_ALL;
    fixture->expected_ctx->extra.client.servername = SSL_TEST_SERVERNAME_SERVER2;
    fixture->expected_ctx->extra.client.npn_protocols =
        OPENSSL_strdup("foo,bar");
    if (!TEST_ptr(fixture->expected_ctx->extra.client.npn_protocols))
        goto err;
    fixture->expected_ctx->extra.client.max_fragment_len_mode = 0;

    fixture->expected_ctx->extra.server.servername_callback =
        SSL_TEST_SERVERNAME_IGNORE_MISMATCH;
    fixture->expected_ctx->extra.server.broken_session_ticket = 1;

    fixture->expected_ctx->resume_extra.server2.alpn_protocols =
        OPENSSL_strdup("baz");
    if (!TEST_ptr(fixture->expected_ctx->resume_extra.server2.alpn_protocols))
        goto err;

    fixture->expected_ctx->resume_extra.client.ct_validation =
        SSL_TEST_CT_VALIDATION_STRICT;

    EXECUTE_SSL_TEST_CTX_TEST();
    return result;

err:
    tear_down(fixture);
    return 0;
}