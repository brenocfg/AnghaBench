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
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  PW_CB_DATA ;
typedef  int /*<<< orphan*/  OSSL_STORE_SEARCH ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;
typedef  int /*<<< orphan*/  OSSL_STORE_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_print_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_print_private (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  OSSL_STORE_INFO_CERT 132 
#define  OSSL_STORE_INFO_CRL 131 
#define  OSSL_STORE_INFO_NAME 130 
#define  OSSL_STORE_INFO_PARAMS 129 
#define  OSSL_STORE_INFO_PKEY 128 
 int /*<<< orphan*/  OSSL_STORE_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_get0_CERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_get0_CRL (int /*<<< orphan*/ *) ; 
 char* OSSL_STORE_INFO_get0_NAME (int /*<<< orphan*/ *) ; 
 char* OSSL_STORE_INFO_get0_NAME_description (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_get0_PARAMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_INFO_get0_PKEY (int /*<<< orphan*/ *) ; 
 int OSSL_STORE_INFO_get_type (int /*<<< orphan*/ *) ; 
 char* OSSL_STORE_INFO_type_string (int) ; 
 int /*<<< orphan*/  OSSL_STORE_close (int /*<<< orphan*/ *) ; 
 scalar_t__ OSSL_STORE_eof (int /*<<< orphan*/ *) ; 
 scalar_t__ OSSL_STORE_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_expect (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSSL_STORE_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_STORE_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_STORE_open (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_supports_search (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PEM_write_bio_Parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEM_write_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEM_write_bio_X509_CRL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_CRL_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  indent_printf (int,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int process(const char *uri, const UI_METHOD *uimeth, PW_CB_DATA *uidata,
                   int expected, int criterion, OSSL_STORE_SEARCH *search,
                   int text, int noout, int recursive, int indent, BIO *out,
                   const char *prog)
{
    OSSL_STORE_CTX *store_ctx = NULL;
    int ret = 1, items = 0;

    if ((store_ctx = OSSL_STORE_open(uri, uimeth, uidata, NULL, NULL))
        == NULL) {
        BIO_printf(bio_err, "Couldn't open file or uri %s\n", uri);
        ERR_print_errors(bio_err);
        return ret;
    }

    if (expected != 0) {
        if (!OSSL_STORE_expect(store_ctx, expected)) {
            ERR_print_errors(bio_err);
            goto end2;
        }
    }

    if (criterion != 0) {
        if (!OSSL_STORE_supports_search(store_ctx, criterion)) {
            BIO_printf(bio_err,
                       "%s: the store scheme doesn't support the given search criteria.\n",
                       prog);
            goto end2;
        }

        if (!OSSL_STORE_find(store_ctx, search)) {
            ERR_print_errors(bio_err);
            goto end2;
        }
    }

    /* From here on, we count errors, and we'll return the count at the end */
    ret = 0;

    for (;;) {
        OSSL_STORE_INFO *info = OSSL_STORE_load(store_ctx);
        int type = info == NULL ? 0 : OSSL_STORE_INFO_get_type(info);
        const char *infostr =
            info == NULL ? NULL : OSSL_STORE_INFO_type_string(type);

        if (info == NULL) {
            if (OSSL_STORE_eof(store_ctx))
                break;

            if (OSSL_STORE_error(store_ctx)) {
                if (recursive)
                    ERR_clear_error();
                else
                    ERR_print_errors(bio_err);
                ret++;
                continue;
            }

            BIO_printf(bio_err,
                       "ERROR: OSSL_STORE_load() returned NULL without "
                       "eof or error indications\n");
            BIO_printf(bio_err, "       This is an error in the loader\n");
            ERR_print_errors(bio_err);
            ret++;
            break;
        }

        if (type == OSSL_STORE_INFO_NAME) {
            const char *name = OSSL_STORE_INFO_get0_NAME(info);
            const char *desc = OSSL_STORE_INFO_get0_NAME_description(info);
            indent_printf(indent, bio_out, "%d: %s: %s\n", items, infostr,
                          name);
            if (desc != NULL)
                indent_printf(indent, bio_out, "%s\n", desc);
        } else {
            indent_printf(indent, bio_out, "%d: %s\n", items, infostr);
        }

        /*
         * Unfortunately, PEM_X509_INFO_write_bio() is sorely lacking in
         * functionality, so we must figure out how exactly to write things
         * ourselves...
         */
        switch (type) {
        case OSSL_STORE_INFO_NAME:
            if (recursive) {
                const char *suburi = OSSL_STORE_INFO_get0_NAME(info);
                ret += process(suburi, uimeth, uidata,
                               expected, criterion, search,
                               text, noout, recursive, indent + 2, out, prog);
            }
            break;
        case OSSL_STORE_INFO_PARAMS:
            if (text)
                EVP_PKEY_print_params(out, OSSL_STORE_INFO_get0_PARAMS(info),
                                      0, NULL);
            if (!noout)
                PEM_write_bio_Parameters(out,
                                         OSSL_STORE_INFO_get0_PARAMS(info));
            break;
        case OSSL_STORE_INFO_PKEY:
            if (text)
                EVP_PKEY_print_private(out, OSSL_STORE_INFO_get0_PKEY(info),
                                       0, NULL);
            if (!noout)
                PEM_write_bio_PrivateKey(out, OSSL_STORE_INFO_get0_PKEY(info),
                                         NULL, NULL, 0, NULL, NULL);
            break;
        case OSSL_STORE_INFO_CERT:
            if (text)
                X509_print(out, OSSL_STORE_INFO_get0_CERT(info));
            if (!noout)
                PEM_write_bio_X509(out, OSSL_STORE_INFO_get0_CERT(info));
            break;
        case OSSL_STORE_INFO_CRL:
            if (text)
                X509_CRL_print(out, OSSL_STORE_INFO_get0_CRL(info));
            if (!noout)
                PEM_write_bio_X509_CRL(out, OSSL_STORE_INFO_get0_CRL(info));
            break;
        default:
            BIO_printf(bio_err, "!!! Unknown code\n");
            ret++;
            break;
        }
        items++;
        OSSL_STORE_INFO_free(info);
    }
    indent_printf(indent, out, "Total found: %d\n", items);

 end2:
    if (!OSSL_STORE_close(store_ctx)) {
        ERR_print_errors(bio_err);
        ret++;
    }

    return ret;
}