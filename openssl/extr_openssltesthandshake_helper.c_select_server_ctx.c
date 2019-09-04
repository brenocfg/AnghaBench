#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* servername; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ HANDSHAKE_EX_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_get_options (int /*<<< orphan*/ *) ; 
 void* SSL_TEST_SERVERNAME_SERVER1 ; 
 void* SSL_TEST_SERVERNAME_SERVER2 ; 
 int SSL_TLSEXT_ERR_ALERT_FATAL ; 
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 int /*<<< orphan*/  SSL_clear_options (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SSL_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* SSL_get_servername (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_SSL_CTX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_NAMETYPE_host_name ; 
 int /*<<< orphan*/  ex_data_idx ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int select_server_ctx(SSL *s, void *arg, int ignore)
{
    const char *servername = SSL_get_servername(s, TLSEXT_NAMETYPE_host_name);
    HANDSHAKE_EX_DATA *ex_data =
        (HANDSHAKE_EX_DATA*)(SSL_get_ex_data(s, ex_data_idx));

    if (servername == NULL) {
        ex_data->servername = SSL_TEST_SERVERNAME_SERVER1;
        return SSL_TLSEXT_ERR_NOACK;
    }

    if (strcmp(servername, "server2") == 0) {
        SSL_CTX *new_ctx = (SSL_CTX*)arg;
        SSL_set_SSL_CTX(s, new_ctx);
        /*
         * Copy over all the SSL_CTX options - reasonable behavior
         * allows testing of cases where the options between two
         * contexts differ/conflict
         */
        SSL_clear_options(s, 0xFFFFFFFFL);
        SSL_set_options(s, SSL_CTX_get_options(new_ctx));

        ex_data->servername = SSL_TEST_SERVERNAME_SERVER2;
        return SSL_TLSEXT_ERR_OK;
    } else if (strcmp(servername, "server1") == 0) {
        ex_data->servername = SSL_TEST_SERVERNAME_SERVER1;
        return SSL_TLSEXT_ERR_OK;
    } else if (ignore) {
        ex_data->servername = SSL_TEST_SERVERNAME_SERVER1;
        return SSL_TLSEXT_ERR_NOACK;
    } else {
        /* Don't set an explicit alert, to test library defaults. */
        return SSL_TLSEXT_ERR_ALERT_FATAL;
    }
}