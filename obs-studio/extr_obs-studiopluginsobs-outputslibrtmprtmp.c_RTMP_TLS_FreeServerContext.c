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

/* Variables and functions */

void
RTMP_TLS_FreeServerContext(void *ctx)
{
#ifdef CRYPTO
#if defined(USE_MBEDTLS)
    mbedtls_x509_crt_free(&((tls_server_ctx*)ctx)->cert);
    mbedtls_pk_free(&((tls_server_ctx*)ctx)->key);
    free(ctx);
#elif defined(USE_POLARSSL)
    x509_free(&((tls_server_ctx*)ctx)->cert);
    rsa_free(&((tls_server_ctx*)ctx)->key);
    free(ctx);
#elif defined(USE_GNUTLS) && !defined(NO_SSL)
    gnutls_certificate_free_credentials(ctx);
#elif !defined(NO_SSL) /* USE_OPENSSL */
    SSL_CTX_free(ctx);
#endif

#else
    (void)ctx;
#endif
}