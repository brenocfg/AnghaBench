#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_5__ {char const* password; char const* prompt_info; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_1__ PW_CB_DATA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ENGINE_load_public_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_ASN1RSA ; 
 int FORMAT_ENGINE ; 
 int FORMAT_MSBLOB ; 
 int FORMAT_PEM ; 
 int FORMAT_PEMRSA ; 
 int /*<<< orphan*/ * PEM_read_bio_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * PEM_read_bio_RSAPublicKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * b2i_PublicKey_bio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char const*,char,int) ; 
 int /*<<< orphan*/ * d2i_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_RSAPublicKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dup_bio_in (int) ; 
 scalar_t__ get_ui_method () ; 
 scalar_t__ password_callback ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  unbuffer (int /*<<< orphan*/ ) ; 

EVP_PKEY *load_pubkey(const char *file, int format, int maybe_stdin,
                      const char *pass, ENGINE *e, const char *key_descrip)
{
    BIO *key = NULL;
    EVP_PKEY *pkey = NULL;
    PW_CB_DATA cb_data;

    cb_data.password = pass;
    cb_data.prompt_info = file;

    if (file == NULL && (!maybe_stdin || format == FORMAT_ENGINE)) {
        BIO_printf(bio_err, "no keyfile specified\n");
        goto end;
    }
    if (format == FORMAT_ENGINE) {
        if (e == NULL) {
            BIO_printf(bio_err, "no engine specified\n");
        } else {
#ifndef OPENSSL_NO_ENGINE
            pkey = ENGINE_load_public_key(e, file, (UI_METHOD *)get_ui_method(),
                                          &cb_data);
            if (pkey == NULL) {
                BIO_printf(bio_err, "cannot load %s from engine\n", key_descrip);
                ERR_print_errors(bio_err);
            }
#else
            BIO_printf(bio_err, "engines not supported\n");
#endif
        }
        goto end;
    }
    if (file == NULL && maybe_stdin) {
        unbuffer(stdin);
        key = dup_bio_in(format);
    } else {
        key = bio_open_default(file, 'r', format);
    }
    if (key == NULL)
        goto end;
    if (format == FORMAT_ASN1) {
        pkey = d2i_PUBKEY_bio(key, NULL);
    } else if (format == FORMAT_ASN1RSA) {
#ifndef OPENSSL_NO_RSA
        RSA *rsa;
        rsa = d2i_RSAPublicKey_bio(key, NULL);
        if (rsa) {
            pkey = EVP_PKEY_new();
            if (pkey != NULL)
                EVP_PKEY_set1_RSA(pkey, rsa);
            RSA_free(rsa);
        } else
#else
        BIO_printf(bio_err, "RSA keys not supported\n");
#endif
            pkey = NULL;
    } else if (format == FORMAT_PEMRSA) {
#ifndef OPENSSL_NO_RSA
        RSA *rsa;
        rsa = PEM_read_bio_RSAPublicKey(key, NULL,
                                        (pem_password_cb *)password_callback,
                                        &cb_data);
        if (rsa != NULL) {
            pkey = EVP_PKEY_new();
            if (pkey != NULL)
                EVP_PKEY_set1_RSA(pkey, rsa);
            RSA_free(rsa);
        } else
#else
        BIO_printf(bio_err, "RSA keys not supported\n");
#endif
            pkey = NULL;
    } else if (format == FORMAT_PEM) {
        pkey = PEM_read_bio_PUBKEY(key, NULL,
                                   (pem_password_cb *)password_callback,
                                   &cb_data);
#if !defined(OPENSSL_NO_RSA) && !defined(OPENSSL_NO_DSA)
    } else if (format == FORMAT_MSBLOB) {
        pkey = b2i_PublicKey_bio(key);
#endif
    }
 end:
    BIO_free(key);
    if (pkey == NULL)
        BIO_printf(bio_err, "unable to load %s\n", key_descrip);
    return pkey;
}