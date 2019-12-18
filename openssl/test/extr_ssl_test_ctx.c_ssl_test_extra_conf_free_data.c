#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  session_ticket_app_data; int /*<<< orphan*/  srp_password; int /*<<< orphan*/  srp_user; int /*<<< orphan*/  alpn_protocols; int /*<<< orphan*/  npn_protocols; } ;
struct TYPE_7__ {int /*<<< orphan*/  session_ticket_app_data; int /*<<< orphan*/  srp_password; int /*<<< orphan*/  srp_user; int /*<<< orphan*/  alpn_protocols; int /*<<< orphan*/  npn_protocols; } ;
struct TYPE_6__ {int /*<<< orphan*/  srp_password; int /*<<< orphan*/  srp_user; int /*<<< orphan*/  reneg_ciphers; int /*<<< orphan*/  alpn_protocols; int /*<<< orphan*/  npn_protocols; } ;
struct TYPE_9__ {TYPE_3__ server2; TYPE_2__ server; TYPE_1__ client; } ;
typedef  TYPE_4__ SSL_TEST_EXTRA_CONF ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssl_test_extra_conf_free_data(SSL_TEST_EXTRA_CONF *conf)
{
    OPENSSL_free(conf->client.npn_protocols);
    OPENSSL_free(conf->server.npn_protocols);
    OPENSSL_free(conf->server2.npn_protocols);
    OPENSSL_free(conf->client.alpn_protocols);
    OPENSSL_free(conf->server.alpn_protocols);
    OPENSSL_free(conf->server2.alpn_protocols);
    OPENSSL_free(conf->client.reneg_ciphers);
    OPENSSL_free(conf->server.srp_user);
    OPENSSL_free(conf->server.srp_password);
    OPENSSL_free(conf->server2.srp_user);
    OPENSSL_free(conf->server2.srp_password);
    OPENSSL_free(conf->client.srp_user);
    OPENSSL_free(conf->client.srp_password);
    OPENSSL_free(conf->server.session_ticket_app_data);
    OPENSSL_free(conf->server2.session_ticket_app_data);
}