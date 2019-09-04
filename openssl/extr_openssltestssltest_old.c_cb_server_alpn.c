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
 scalar_t__ OPENSSL_NPN_NEGOTIATED ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (unsigned char) ; 
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 scalar_t__ SSL_select_next_proto (unsigned char**,unsigned char*,unsigned char*,size_t,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  abort () ; 
 unsigned char* alpn_selected ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned char) ; 
 unsigned char* next_protos_parse (size_t*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int cb_server_alpn(SSL *s, const unsigned char **out,
                          unsigned char *outlen, const unsigned char *in,
                          unsigned int inlen, void *arg)
{
    unsigned char *protos;
    size_t protos_len;
    char* alpn_str = arg;

    protos = next_protos_parse(&protos_len, alpn_str);
    if (protos == NULL) {
        fprintf(stderr, "failed to parser ALPN server protocol string: %s\n",
                alpn_str);
        abort();
    }

    if (SSL_select_next_proto
        ((unsigned char **)out, outlen, protos, protos_len, in,
         inlen) != OPENSSL_NPN_NEGOTIATED) {
        OPENSSL_free(protos);
        return SSL_TLSEXT_ERR_NOACK;
    }

    /*
     * Make a copy of the selected protocol which will be freed in
     * verify_alpn.
     */
    alpn_selected = OPENSSL_malloc(*outlen);
    memcpy(alpn_selected, *out, *outlen);
    *out = alpn_selected;

    OPENSSL_free(protos);
    return SSL_TLSEXT_ERR_OK;
}