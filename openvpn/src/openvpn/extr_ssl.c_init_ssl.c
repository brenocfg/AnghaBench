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
struct tls_root_ctx {int dummy; } ;
struct options {int ssl_flags; int management_flags; char* cert_file_inline; int /*<<< orphan*/  ecdh_curve; int /*<<< orphan*/  tls_server; int /*<<< orphan*/  crl_file_inline; int /*<<< orphan*/  crl_file; int /*<<< orphan*/  extra_certs_file_inline; int /*<<< orphan*/  extra_certs_file; int /*<<< orphan*/  ca_path; int /*<<< orphan*/  ca_file_inline; scalar_t__ ca_file; int /*<<< orphan*/  priv_key_file_inline; int /*<<< orphan*/  priv_key_file; int /*<<< orphan*/  cert_file; int /*<<< orphan*/  management_certificate; int /*<<< orphan*/  cryptoapi_cert; int /*<<< orphan*/  pkcs11_id; int /*<<< orphan*/  pkcs11_id_management; scalar_t__* pkcs11_providers; int /*<<< orphan*/  pkcs12_file_inline; int /*<<< orphan*/  pkcs12_file; int /*<<< orphan*/  cipher_list_tls13; int /*<<< orphan*/  cipher_list; int /*<<< orphan*/  tls_cert_profile; int /*<<< orphan*/  dh_file_inline; int /*<<< orphan*/  dh_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INLINE_FILE_TAG ; 
 int MF_EXTERNAL_CERT ; 
 int MF_EXTERNAL_KEY ; 
 int /*<<< orphan*/  M_WARN ; 
 int SSLF_CRL_VERIFY_DIR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  management ; 
 char* management_query_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tls_clear_error () ; 
 int /*<<< orphan*/  tls_ctx_check_cert_time (struct tls_root_ctx*) ; 
 int /*<<< orphan*/  tls_ctx_client_new (struct tls_root_ctx*) ; 
 int /*<<< orphan*/  tls_ctx_free (struct tls_root_ctx*) ; 
 int /*<<< orphan*/  tls_ctx_load_ca (struct tls_root_ctx*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_load_cert_file (struct tls_root_ctx*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tls_ctx_load_cryptoapi (struct tls_root_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_load_dh_params (struct tls_root_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_load_ecdh_params (struct tls_root_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_load_extra_certs (struct tls_root_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tls_ctx_load_pkcs12 (struct tls_root_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tls_ctx_load_priv_file (struct tls_root_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_personalise_random (struct tls_root_ctx*) ; 
 int /*<<< orphan*/  tls_ctx_reload_crl (struct tls_root_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_restrict_ciphers (struct tls_root_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_restrict_ciphers_tls13 (struct tls_root_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_server_new (struct tls_root_ctx*) ; 
 int /*<<< orphan*/  tls_ctx_set_cert_profile (struct tls_root_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_ctx_set_options (struct tls_root_ctx*,int) ; 
 scalar_t__ tls_ctx_use_management_external_key (struct tls_root_ctx*) ; 
 int /*<<< orphan*/  tls_ctx_use_pkcs11 (struct tls_root_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
init_ssl(const struct options *options, struct tls_root_ctx *new_ctx)
{
    ASSERT(NULL != new_ctx);

    tls_clear_error();

    if (options->tls_server)
    {
        tls_ctx_server_new(new_ctx);

        if (options->dh_file)
        {
            tls_ctx_load_dh_params(new_ctx, options->dh_file,
                                   options->dh_file_inline);
        }
    }
    else                        /* if client */
    {
        tls_ctx_client_new(new_ctx);
    }

    /* Restrict allowed certificate crypto algorithms */
    tls_ctx_set_cert_profile(new_ctx, options->tls_cert_profile);

    /* Allowable ciphers */
    /* Since @SECLEVEL also influences loading of certificates, set the
     * cipher restrictions before loading certificates */
    tls_ctx_restrict_ciphers(new_ctx, options->cipher_list);
    tls_ctx_restrict_ciphers_tls13(new_ctx, options->cipher_list_tls13);

    if (!tls_ctx_set_options(new_ctx, options->ssl_flags))
    {
        goto err;
    }

    if (options->pkcs12_file)
    {
        if (0 != tls_ctx_load_pkcs12(new_ctx, options->pkcs12_file,
                                     options->pkcs12_file_inline, !options->ca_file))
        {
            goto err;
        }
    }
#ifdef ENABLE_PKCS11
    else if (options->pkcs11_providers[0])
    {
        if (!tls_ctx_use_pkcs11(new_ctx, options->pkcs11_id_management, options->pkcs11_id))
        {
            msg(M_WARN, "Cannot load certificate \"%s\" using PKCS#11 interface",
                options->pkcs11_id);
            goto err;
        }
    }
#endif
#ifdef ENABLE_CRYPTOAPI
    else if (options->cryptoapi_cert)
    {
        tls_ctx_load_cryptoapi(new_ctx, options->cryptoapi_cert);
    }
#endif
#ifdef ENABLE_MANAGEMENT
    else if (options->management_flags & MF_EXTERNAL_CERT)
    {
        char *cert = management_query_cert(management,
                                           options->management_certificate);
        tls_ctx_load_cert_file(new_ctx, INLINE_FILE_TAG, cert);
        free(cert);
    }
#endif
    else if (options->cert_file)
    {
        tls_ctx_load_cert_file(new_ctx, options->cert_file, options->cert_file_inline);
    }

    if (options->priv_key_file)
    {
        if (0 != tls_ctx_load_priv_file(new_ctx, options->priv_key_file,
                                        options->priv_key_file_inline))
        {
            goto err;
        }
    }
#ifdef ENABLE_MANAGEMENT
    else if (options->management_flags & MF_EXTERNAL_KEY)
    {
        if (tls_ctx_use_management_external_key(new_ctx))
        {
            msg(M_WARN, "Cannot initialize mamagement-external-key");
            goto err;
        }
    }
#endif

    if (options->ca_file || options->ca_path)
    {
        tls_ctx_load_ca(new_ctx, options->ca_file, options->ca_file_inline,
                        options->ca_path, options->tls_server);
    }

    /* Load extra certificates that are part of our own certificate
     * chain but shouldn't be included in the verify chain */
    if (options->extra_certs_file)
    {
        tls_ctx_load_extra_certs(new_ctx, options->extra_certs_file, options->extra_certs_file_inline);
    }

    /* Check certificate notBefore and notAfter */
    tls_ctx_check_cert_time(new_ctx);

    /* Read CRL */
    if (options->crl_file && !(options->ssl_flags & SSLF_CRL_VERIFY_DIR))
    {
        tls_ctx_reload_crl(new_ctx, options->crl_file, options->crl_file_inline);
    }

    /* Once keys and cert are loaded, load ECDH parameters */
    if (options->tls_server)
    {
        tls_ctx_load_ecdh_params(new_ctx, options->ecdh_curve);
    }

#ifdef ENABLE_CRYPTO_MBEDTLS
    /* Personalise the random by mixing in the certificate */
    tls_ctx_personalise_random(new_ctx);
#endif

    tls_clear_error();
    return;

err:
    tls_clear_error();
    tls_ctx_free(new_ctx);
    return;
}