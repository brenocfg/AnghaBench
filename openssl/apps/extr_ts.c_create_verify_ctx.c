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
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;
typedef  int /*<<< orphan*/  TS_VERIFY_CTX ;
typedef  int /*<<< orphan*/  TS_REQ ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 unsigned char* OPENSSL_hexstr2buf (char const*,long*) ; 
 int /*<<< orphan*/  TS_CONF_load_certs (char const*) ; 
 int /*<<< orphan*/  TS_REQ_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_REQ_to_TS_VERIFY_CTX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_VERIFY_CTX_add_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TS_VERIFY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_VERIFY_CTX_new () ; 
 int /*<<< orphan*/ * TS_VERIFY_CTX_set_certs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TS_VERIFY_CTX_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_VERIFY_CTX_set_imprint (int /*<<< orphan*/ *,unsigned char*,long) ; 
 int /*<<< orphan*/ * TS_VERIFY_CTX_set_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TS_VFY_DATA ; 
 int TS_VFY_IMPRINT ; 
 int TS_VFY_SIGNATURE ; 
 int TS_VFY_SIGNER ; 
 int TS_VFY_VERSION ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  create_cert_store (char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_TS_REQ_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TS_VERIFY_CTX *create_verify_ctx(const char *data, const char *digest,
                                        const char *queryfile,
                                        const char *CApath, const char *CAfile,
                                        const char *CAstore,
                                        const char *untrusted,
                                        X509_VERIFY_PARAM *vpm)
{
    TS_VERIFY_CTX *ctx = NULL;
    BIO *input = NULL;
    TS_REQ *request = NULL;
    int ret = 0;
    int f = 0;

    if (data != NULL || digest != NULL) {
        if ((ctx = TS_VERIFY_CTX_new()) == NULL)
            goto err;
        f = TS_VFY_VERSION | TS_VFY_SIGNER;
        if (data != NULL) {
            BIO *out = NULL;

            f |= TS_VFY_DATA;
            if ((out = BIO_new_file(data, "rb")) == NULL)
                goto err;
            if (TS_VERIFY_CTX_set_data(ctx, out) == NULL) {
                BIO_free_all(out);
                goto err;
            }
        } else if (digest != NULL) {
            long imprint_len;
            unsigned char *hexstr = OPENSSL_hexstr2buf(digest, &imprint_len);
            f |= TS_VFY_IMPRINT;
            if (TS_VERIFY_CTX_set_imprint(ctx, hexstr, imprint_len) == NULL) {
                BIO_printf(bio_err, "invalid digest string\n");
                goto err;
            }
        }

    } else if (queryfile != NULL) {
        if ((input = BIO_new_file(queryfile, "rb")) == NULL)
            goto err;
        if ((request = d2i_TS_REQ_bio(input, NULL)) == NULL)
            goto err;
        if ((ctx = TS_REQ_to_TS_VERIFY_CTX(request, NULL)) == NULL)
            goto err;
    } else {
        return NULL;
    }

    /* Add the signature verification flag and arguments. */
    TS_VERIFY_CTX_add_flags(ctx, f | TS_VFY_SIGNATURE);

    /* Initialising the X509_STORE object. */
    if (TS_VERIFY_CTX_set_store(ctx,
                                create_cert_store(CApath, CAfile, CAstore, vpm))
            == NULL)
        goto err;

    /* Loading untrusted certificates. */
    if (untrusted
        && TS_VERIFY_CTX_set_certs(ctx, TS_CONF_load_certs(untrusted)) == NULL)
        goto err;
    ret = 1;

 err:
    if (!ret) {
        TS_VERIFY_CTX_free(ctx);
        ctx = NULL;
    }
    BIO_free_all(input);
    TS_REQ_free(request);
    return ctx;
}