#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int client_alert_sent; int client_alert_received; int server_alert_sent; int server_alert_received; int /*<<< orphan*/  server_num_fatal_alerts_sent; int /*<<< orphan*/  client_num_fatal_alerts_sent; } ;
struct TYPE_5__ {int expected_client_alert; int expected_server_alert; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;
typedef  TYPE_2__ HANDSHAKE_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_alert (int) ; 

__attribute__((used)) static int check_alerts(HANDSHAKE_RESULT *result, SSL_TEST_CTX *test_ctx)
{
    if (!TEST_int_eq(result->client_alert_sent,
                     result->client_alert_received)) {
        TEST_info("Client sent alert %s but server received %s.",
                  print_alert(result->client_alert_sent),
                  print_alert(result->client_alert_received));
        /*
         * We can't bail here because the peer doesn't always get far enough
         * to process a received alert. Specifically, in protocol version
         * negotiation tests, we have the following scenario.
         * Client supports TLS v1.2 only; Server supports TLS v1.1.
         * Client proposes TLS v1.2; server responds with 1.1;
         * Client now sends a protocol alert, using TLS v1.2 in the header.
         * The server, however, rejects the alert because of version mismatch
         * in the record layer; therefore, the server appears to never
         * receive the alert.
         */
        /* return 0; */
    }

    if (!TEST_int_eq(result->server_alert_sent,
                     result->server_alert_received)) {
        TEST_info("Server sent alert %s but client received %s.",
                  print_alert(result->server_alert_sent),
                  print_alert(result->server_alert_received));
        /* return 0; */
    }

    /* Tolerate an alert if one wasn't explicitly specified in the test. */
    if (test_ctx->expected_client_alert
        /*
         * The info callback alert value is computed as
         * (s->s3->send_alert[0] << 8) | s->s3->send_alert[1]
         * where the low byte is the alert code and the high byte is other stuff.
         */
        && (result->client_alert_sent & 0xff) != test_ctx->expected_client_alert) {
        TEST_error("ClientAlert mismatch: expected %s, got %s.",
                   print_alert(test_ctx->expected_client_alert),
                   print_alert(result->client_alert_sent));
        return 0;
    }

    if (test_ctx->expected_server_alert
        && (result->server_alert_sent & 0xff) != test_ctx->expected_server_alert) {
        TEST_error("ServerAlert mismatch: expected %s, got %s.",
                   print_alert(test_ctx->expected_server_alert),
                   print_alert(result->server_alert_sent));
        return 0;
    }

    if (!TEST_int_le(result->client_num_fatal_alerts_sent, 1))
        return 0;
    if (!TEST_int_le(result->server_num_fatal_alerts_sent, 1))
        return 0;
    return 1;
}