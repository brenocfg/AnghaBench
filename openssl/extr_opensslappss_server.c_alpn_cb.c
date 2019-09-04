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
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ tlsextalpnctx ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ ,...) ; 
 scalar_t__ OPENSSL_NPN_NEGOTIATED ; 
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 scalar_t__ SSL_select_next_proto (unsigned char**,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  bio_s_out ; 
 int /*<<< orphan*/  s_quiet ; 

__attribute__((used)) static int alpn_cb(SSL *s, const unsigned char **out, unsigned char *outlen,
                   const unsigned char *in, unsigned int inlen, void *arg)
{
    tlsextalpnctx *alpn_ctx = arg;

    if (!s_quiet) {
        /* We can assume that |in| is syntactically valid. */
        unsigned int i;
        BIO_printf(bio_s_out, "ALPN protocols advertised by the client: ");
        for (i = 0; i < inlen;) {
            if (i)
                BIO_write(bio_s_out, ", ", 2);
            BIO_write(bio_s_out, &in[i + 1], in[i]);
            i += in[i] + 1;
        }
        BIO_write(bio_s_out, "\n", 1);
    }

    if (SSL_select_next_proto
        ((unsigned char **)out, outlen, alpn_ctx->data, alpn_ctx->len, in,
         inlen) != OPENSSL_NPN_NEGOTIATED) {
        return SSL_TLSEXT_ERR_NOACK;
    }

    if (!s_quiet) {
        BIO_printf(bio_s_out, "ALPN protocols selected: ");
        BIO_write(bio_s_out, *out, *outlen);
        BIO_write(bio_s_out, "\n", 1);
    }

    return SSL_TLSEXT_ERR_OK;
}