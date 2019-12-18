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
struct TYPE_2__ {int /*<<< orphan*/  alpn_protocols_len; int /*<<< orphan*/  alpn_protocols; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ CTX_DATA ;

/* Variables and functions */
 int OPENSSL_NPN_NEGOTIATED ; 
 int SSL_TLSEXT_ERR_ALERT_FATAL ; 
 int SSL_TLSEXT_ERR_OK ; 
 int SSL_select_next_proto (unsigned char**,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

__attribute__((used)) static int server_alpn_cb(SSL *s, const unsigned char **out,
                          unsigned char *outlen, const unsigned char *in,
                          unsigned int inlen, void *arg)
{
    CTX_DATA *ctx_data = (CTX_DATA*)(arg);
    int ret;

    /* SSL_select_next_proto isn't const-correct... */
    unsigned char *tmp_out;

    /*
     * The result points either to |in| or to |ctx_data->alpn_protocols|.
     * The callback is allowed to point to |in| or to a long-lived buffer,
     * so we can return directly without storing a copy.
     */
    ret = SSL_select_next_proto(&tmp_out, outlen,
                                ctx_data->alpn_protocols,
                                ctx_data->alpn_protocols_len, in, inlen);

    *out = tmp_out;
    /* Unlike NPN, we don't tolerate a mismatch. */
    return ret == OPENSSL_NPN_NEGOTIATED ? SSL_TLSEXT_ERR_OK
        : SSL_TLSEXT_ERR_ALERT_FATAL;
}