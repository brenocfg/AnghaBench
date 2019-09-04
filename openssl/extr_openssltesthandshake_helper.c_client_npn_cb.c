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
struct TYPE_2__ {int /*<<< orphan*/  npn_protocols_len; int /*<<< orphan*/  npn_protocols; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ CTX_DATA ;

/* Variables and functions */
 int OPENSSL_NPN_NEGOTIATED ; 
 int OPENSSL_NPN_NO_OVERLAP ; 
 int SSL_TLSEXT_ERR_ALERT_FATAL ; 
 int SSL_TLSEXT_ERR_OK ; 
 int SSL_select_next_proto (unsigned char**,unsigned char*,unsigned char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_true (int) ; 

__attribute__((used)) static int client_npn_cb(SSL *s, unsigned char **out, unsigned char *outlen,
                         const unsigned char *in, unsigned int inlen,
                         void *arg)
{
    CTX_DATA *ctx_data = (CTX_DATA*)(arg);
    int ret;

    ret = SSL_select_next_proto(out, outlen, in, inlen,
                                ctx_data->npn_protocols,
                                ctx_data->npn_protocols_len);
    /* Accept both OPENSSL_NPN_NEGOTIATED and OPENSSL_NPN_NO_OVERLAP. */
    return TEST_true(ret == OPENSSL_NPN_NEGOTIATED || ret == OPENSSL_NPN_NO_OVERLAP)
        ? SSL_TLSEXT_ERR_OK : SSL_TLSEXT_ERR_ALERT_FATAL;
}