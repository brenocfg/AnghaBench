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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_ASN1_METHOD ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_keygen_bits (int /*<<< orphan*/ *,long) ; 
 int EVP_PKEY_RSA ; 
 int /*<<< orphan*/ * EVP_PKEY_asn1_find (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * EVP_PKEY_asn1_find_str (int /*<<< orphan*/ **,char const*,int) ; 
 int /*<<< orphan*/  EVP_PKEY_asn1_get0_info (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_base_id (int /*<<< orphan*/ *) ; 
 long EVP_PKEY_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/ * PEM_read_bio_Parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_pubkey (int /*<<< orphan*/ *) ; 
 long atol (char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static EVP_PKEY_CTX *set_keygen_ctx(const char *gstr,
                                    int *pkey_type, long *pkeylen,
                                    char **palgnam, ENGINE *keygen_engine)
{
    EVP_PKEY_CTX *gctx = NULL;
    EVP_PKEY *param = NULL;
    long keylen = -1;
    BIO *pbio = NULL;
    const char *paramfile = NULL;

    if (gstr == NULL) {
        *pkey_type = EVP_PKEY_RSA;
        keylen = *pkeylen;
    } else if (gstr[0] >= '0' && gstr[0] <= '9') {
        *pkey_type = EVP_PKEY_RSA;
        keylen = atol(gstr);
        *pkeylen = keylen;
    } else if (strncmp(gstr, "param:", 6) == 0) {
        paramfile = gstr + 6;
    } else {
        const char *p = strchr(gstr, ':');
        int len;
        ENGINE *tmpeng;
        const EVP_PKEY_ASN1_METHOD *ameth;

        if (p != NULL)
            len = p - gstr;
        else
            len = strlen(gstr);
        /*
         * The lookup of a the string will cover all engines so keep a note
         * of the implementation.
         */

        ameth = EVP_PKEY_asn1_find_str(&tmpeng, gstr, len);

        if (ameth == NULL) {
            BIO_printf(bio_err, "Unknown algorithm %.*s\n", len, gstr);
            return NULL;
        }

        EVP_PKEY_asn1_get0_info(NULL, pkey_type, NULL, NULL, NULL, ameth);
#ifndef OPENSSL_NO_ENGINE
        ENGINE_finish(tmpeng);
#endif
        if (*pkey_type == EVP_PKEY_RSA) {
            if (p != NULL) {
                keylen = atol(p + 1);
                *pkeylen = keylen;
            } else {
                keylen = *pkeylen;
            }
        } else if (p != NULL) {
            paramfile = p + 1;
        }
    }

    if (paramfile != NULL) {
        pbio = BIO_new_file(paramfile, "r");
        if (pbio == NULL) {
            BIO_printf(bio_err, "Can't open parameter file %s\n", paramfile);
            return NULL;
        }
        param = PEM_read_bio_Parameters(pbio, NULL);

        if (param == NULL) {
            X509 *x;

            (void)BIO_reset(pbio);
            x = PEM_read_bio_X509(pbio, NULL, NULL, NULL);
            if (x != NULL) {
                param = X509_get_pubkey(x);
                X509_free(x);
            }
        }

        BIO_free(pbio);

        if (param == NULL) {
            BIO_printf(bio_err, "Error reading parameter file %s\n", paramfile);
            return NULL;
        }
        if (*pkey_type == -1) {
            *pkey_type = EVP_PKEY_id(param);
        } else if (*pkey_type != EVP_PKEY_base_id(param)) {
            BIO_printf(bio_err, "Key Type does not match parameters\n");
            EVP_PKEY_free(param);
            return NULL;
        }
    }

    if (palgnam != NULL) {
        const EVP_PKEY_ASN1_METHOD *ameth;
        ENGINE *tmpeng;
        const char *anam;

        ameth = EVP_PKEY_asn1_find(&tmpeng, *pkey_type);
        if (ameth == NULL) {
            BIO_puts(bio_err, "Internal error: can't find key algorithm\n");
            return NULL;
        }
        EVP_PKEY_asn1_get0_info(NULL, NULL, NULL, NULL, &anam, ameth);
        *palgnam = OPENSSL_strdup(anam);
#ifndef OPENSSL_NO_ENGINE
        ENGINE_finish(tmpeng);
#endif
    }

    if (param != NULL) {
        gctx = EVP_PKEY_CTX_new(param, keygen_engine);
        *pkeylen = EVP_PKEY_bits(param);
        EVP_PKEY_free(param);
    } else {
        gctx = EVP_PKEY_CTX_new_id(*pkey_type, keygen_engine);
    }

    if (gctx == NULL) {
        BIO_puts(bio_err, "Error allocating keygen context\n");
        ERR_print_errors(bio_err);
        return NULL;
    }

    if (EVP_PKEY_keygen_init(gctx) <= 0) {
        BIO_puts(bio_err, "Error initializing keygen context\n");
        ERR_print_errors(bio_err);
        EVP_PKEY_CTX_free(gctx);
        return NULL;
    }
#ifndef OPENSSL_NO_RSA
    if ((*pkey_type == EVP_PKEY_RSA) && (keylen != -1)) {
        if (EVP_PKEY_CTX_set_rsa_keygen_bits(gctx, keylen) <= 0) {
            BIO_puts(bio_err, "Error setting RSA keysize\n");
            ERR_print_errors(bio_err);
            EVP_PKEY_CTX_free(gctx);
            return NULL;
        }
    }
#endif

    return gctx;
}