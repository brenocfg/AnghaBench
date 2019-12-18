#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cert; int /*<<< orphan*/  key; int /*<<< orphan*/ * hs; int /*<<< orphan*/  dhm_G; int /*<<< orphan*/  dhm_P; int /*<<< orphan*/ * ctr_drbg; int /*<<< orphan*/ * conf; } ;
typedef  TYPE_1__ tls_server_ctx ;
struct tls_server_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  gnutls_certificate_credentials ;
struct TYPE_5__ {int /*<<< orphan*/  hs; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_X509_FMT_PEM ; 
 int /*<<< orphan*/  RTMP_TLS_Init () ; 
 TYPE_3__* RTMP_TLS_ctx ; 
 int /*<<< orphan*/  SSL_CTX_free (void*) ; 
 void* SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (void*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (void*,char const*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  SSLv23_server_method () ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gnutls_certificate_allocate_credentials (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnutls_certificate_free_credentials (void*) ; 
 scalar_t__ gnutls_certificate_set_x509_key_file (void*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_pk_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_pk_parse_keyfile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_x509_crt_parse_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  my_dhm_G ; 
 int /*<<< orphan*/  my_dhm_P ; 
 int /*<<< orphan*/  x509_free (int /*<<< orphan*/ *) ; 
 scalar_t__ x509parse_crtfile (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ x509parse_keyfile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

void *
RTMP_TLS_AllocServerContext(const char* cert, const char* key)
{
    void *ctx = NULL;
#ifdef CRYPTO
    if (!RTMP_TLS_ctx)
        RTMP_TLS_Init();
#if defined(USE_MBEDTLS)
    tls_server_ctx *tc = ctx = calloc(1, sizeof(struct tls_server_ctx));
    tc->conf = &RTMP_TLS_ctx->conf;
    tc->ctr_drbg = &RTMP_TLS_ctx->ctr_drbg;

    mbedtls_x509_crt_init(&tc->cert);
    if (mbedtls_x509_crt_parse_file(&tc->cert, cert))
    {
        free(tc);
        return NULL;
    }

    mbedtls_pk_init(&tc->key);
    if (mbedtls_pk_parse_keyfile(&tc->key, key, NULL))
    {
        mbedtls_x509_crt_free(&tc->cert);
        mbedtls_pk_free(&tc->key);
        free(tc);
        return NULL;
    }
#elif defined(USE_POLARSSL)
    tls_server_ctx *tc = ctx = calloc(1, sizeof(struct tls_server_ctx));
    tc->dhm_P = my_dhm_P;
    tc->dhm_G = my_dhm_G;
    tc->hs = &RTMP_TLS_ctx->hs;
    if (x509parse_crtfile(&tc->cert, cert))
    {
        free(tc);
        return NULL;
    }
    if (x509parse_keyfile(&tc->key, key, NULL))
    {
        x509_free(&tc->cert);
        free(tc);
        return NULL;
    }
#elif defined(USE_GNUTLS) && !defined(NO_SSL)
    gnutls_certificate_allocate_credentials((gnutls_certificate_credentials*) &ctx);
    if (gnutls_certificate_set_x509_key_file(ctx, cert, key, GNUTLS_X509_FMT_PEM) != 0)
    {
        gnutls_certificate_free_credentials(ctx);
        return NULL;
    }
#elif !defined(NO_SSL) /* USE_OPENSSL */
    ctx = SSL_CTX_new(SSLv23_server_method());
    if (!SSL_CTX_use_certificate_chain_file(ctx, cert))
    {
        SSL_CTX_free(ctx);
        return NULL;
    }
    if (!SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM))
    {
        SSL_CTX_free(ctx);
        return NULL;
    }
#endif
#else
    (void)cert;
    (void)key;
#endif
    return ctx;
}