#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tls_ctx {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cred; int /*<<< orphan*/  prios; int /*<<< orphan*/  hs; int /*<<< orphan*/  entropy; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_X509_FMT_PEM ; 
 int /*<<< orphan*/  OpenSSL_add_all_digests () ; 
 int /*<<< orphan*/  RTMP_TLS_LoadCerts () ; 
 TYPE_1__* RTMP_TLS_ctx ; 
 TYPE_1__* SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_default_verify_paths (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_OP_ALL ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  SSLv23_method () ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  gnutls_certificate_allocate_credentials (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnutls_certificate_set_x509_trust_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_global_init () ; 
 int /*<<< orphan*/  gnutls_priority_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  havege_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_entropy_func ; 
 int /*<<< orphan*/  mbedtls_entropy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
RTMP_TLS_Init()
{
#ifdef CRYPTO
#if defined(USE_MBEDTLS)
    const char * pers = "RTMP_TLS";
    RTMP_TLS_ctx = calloc(1,sizeof(struct tls_ctx));

    mbedtls_ssl_config_init(&RTMP_TLS_ctx->conf);
    mbedtls_ctr_drbg_init(&RTMP_TLS_ctx->ctr_drbg);
    mbedtls_entropy_init(&RTMP_TLS_ctx->entropy);

    mbedtls_ctr_drbg_seed(&RTMP_TLS_ctx->ctr_drbg,
                          mbedtls_entropy_func,
                          &RTMP_TLS_ctx->entropy,
                          (const unsigned char *)pers,
                          strlen(pers));

    RTMP_TLS_LoadCerts();
#elif defined(USE_POLARSSL)
    /* Do this regardless of NO_SSL, we use havege for rtmpe too */
    RTMP_TLS_ctx = calloc(1,sizeof(struct tls_ctx));
    havege_init(&RTMP_TLS_ctx->hs);
#elif defined(USE_GNUTLS) && !defined(NO_SSL)
    /* Technically we need to initialize libgcrypt ourselves if
     * we're not going to call gnutls_global_init(). Ignoring this
     * for now.
     */
    gnutls_global_init();
    RTMP_TLS_ctx = malloc(sizeof(struct tls_ctx));
    gnutls_certificate_allocate_credentials(&RTMP_TLS_ctx->cred);
    gnutls_priority_init(&RTMP_TLS_ctx->prios, "NORMAL", NULL);
    gnutls_certificate_set_x509_trust_file(RTMP_TLS_ctx->cred,
                                           "ca.pem", GNUTLS_X509_FMT_PEM);
#elif !defined(NO_SSL) /* USE_OPENSSL */
    /* libcrypto doesn't need anything special */
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_digests();
    RTMP_TLS_ctx = SSL_CTX_new(SSLv23_method());
    SSL_CTX_set_options(RTMP_TLS_ctx, SSL_OP_ALL);
    SSL_CTX_set_default_verify_paths(RTMP_TLS_ctx);
#endif
#else
#endif
}