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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 unsigned int SSL3_VERSION ; 
 int SSL_AD_INTERNAL_ERROR ; 
 int SSL_AD_PROTOCOL_VERSION ; 
 int SSL_AD_UNRECOGNIZED_NAME ; 
 int SSL_CLIENT_HELLO_ERROR ; 
 int SSL_CLIENT_HELLO_SUCCESS ; 
 scalar_t__ SSL_client_hello_get0_ciphers (int /*<<< orphan*/ *,unsigned char const**) ; 
 scalar_t__ SSL_client_hello_get0_compression_methods (int /*<<< orphan*/ *,unsigned char const**) ; 
 unsigned int SSL_client_hello_get0_legacy_version (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_client_hello_get0_random (int /*<<< orphan*/ *,unsigned char const**) ; 
 int /*<<< orphan*/  SSL_client_hello_get0_session_id (int /*<<< orphan*/ *,unsigned char const**) ; 
 int /*<<< orphan*/  SSL_set_max_proto_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_1_VERSION ; 
 unsigned int TLS1_2_VERSION ; 
 int client_hello_select_server_ctx (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_hello_nov12_cb(SSL *s, int *al, void *arg)
{
    int ret;
    unsigned int v;
    const unsigned char *p;

    v = SSL_client_hello_get0_legacy_version(s);
    if (v > TLS1_2_VERSION || v < SSL3_VERSION) {
        *al = SSL_AD_PROTOCOL_VERSION;
        return SSL_CLIENT_HELLO_ERROR;
    }
    (void)SSL_client_hello_get0_session_id(s, &p);
    if (p == NULL ||
        SSL_client_hello_get0_random(s, &p) == 0 ||
        SSL_client_hello_get0_ciphers(s, &p) == 0 ||
        SSL_client_hello_get0_compression_methods(s, &p) == 0) {
        *al = SSL_AD_INTERNAL_ERROR;
        return SSL_CLIENT_HELLO_ERROR;
    }
    ret = client_hello_select_server_ctx(s, arg, 0);
    SSL_set_max_proto_version(s, TLS1_1_VERSION);
    if (!ret) {
        *al = SSL_AD_UNRECOGNIZED_NAME;
        return SSL_CLIENT_HELLO_ERROR;
    }
    return SSL_CLIENT_HELLO_SUCCESS;
}