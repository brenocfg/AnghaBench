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
typedef  int /*<<< orphan*/  TS_RESP_CTX ;
typedef  int /*<<< orphan*/  TS_RESP ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 char* TS_CONF_get_tsa_section (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  TS_CONF_set_accuracy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_certs (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_clock_precision_digits (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_crypto_device (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  TS_CONF_set_def_policy (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_digests (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_ess_cert_id_chain (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_ess_cert_id_digest (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_ordering (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_policies (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_serial (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_signer_cert (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_signer_digest (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_signer_key (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_CONF_set_tsa_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_RESP_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_RESP_CTX_new () ; 
 int /*<<< orphan*/  TS_RESP_CTX_set_signer_digest (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * TS_RESP_create_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_RESP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_cb ; 

__attribute__((used)) static TS_RESP *create_response(CONF *conf, const char *section, const char *engine,
                                const char *queryfile, const char *passin,
                                const char *inkey, const EVP_MD *md, const char *signer,
                                const char *chain, const char *policy)
{
    int ret = 0;
    TS_RESP *response = NULL;
    BIO *query_bio = NULL;
    TS_RESP_CTX *resp_ctx = NULL;

    if ((query_bio = BIO_new_file(queryfile, "rb")) == NULL)
        goto end;
    if ((section = TS_CONF_get_tsa_section(conf, section)) == NULL)
        goto end;
    if ((resp_ctx = TS_RESP_CTX_new()) == NULL)
        goto end;
    if (!TS_CONF_set_serial(conf, section, serial_cb, resp_ctx))
        goto end;
# ifndef OPENSSL_NO_ENGINE
    if (!TS_CONF_set_crypto_device(conf, section, engine))
        goto end;
# endif
    if (!TS_CONF_set_signer_cert(conf, section, signer, resp_ctx))
        goto end;
    if (!TS_CONF_set_certs(conf, section, chain, resp_ctx))
        goto end;
    if (!TS_CONF_set_signer_key(conf, section, inkey, passin, resp_ctx))
        goto end;

    if (md) {
        if (!TS_RESP_CTX_set_signer_digest(resp_ctx, md))
            goto end;
    } else if (!TS_CONF_set_signer_digest(conf, section, NULL, resp_ctx)) {
            goto end;
    }

    if (!TS_CONF_set_ess_cert_id_digest(conf, section, resp_ctx))
        goto end;
    if (!TS_CONF_set_def_policy(conf, section, policy, resp_ctx))
        goto end;
    if (!TS_CONF_set_policies(conf, section, resp_ctx))
        goto end;
    if (!TS_CONF_set_digests(conf, section, resp_ctx))
        goto end;
    if (!TS_CONF_set_accuracy(conf, section, resp_ctx))
        goto end;
    if (!TS_CONF_set_clock_precision_digits(conf, section, resp_ctx))
        goto end;
    if (!TS_CONF_set_ordering(conf, section, resp_ctx))
        goto end;
    if (!TS_CONF_set_tsa_name(conf, section, resp_ctx))
        goto end;
    if (!TS_CONF_set_ess_cert_id_chain(conf, section, resp_ctx))
        goto end;
    if ((response = TS_RESP_create_response(resp_ctx, query_bio)) == NULL)
        goto end;
    ret = 1;

 end:
    if (!ret) {
        TS_RESP_free(response);
        response = NULL;
    }
    TS_RESP_CTX_free(resp_ctx);
    BIO_free_all(query_bio);
    return response;
}