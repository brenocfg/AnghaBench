#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_6__ {char const* password; char const* prompt_info; } ;
typedef  TYPE_1__ PW_CB_DATA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 scalar_t__ ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_load_private_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_ENGINE ; 
 int FORMAT_MSBLOB ; 
 int FORMAT_PEM ; 
 int FORMAT_PKCS12 ; 
 int FORMAT_PVK ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * b2i_PVK_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * b2i_PrivateKey_bio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char const*,char,int) ; 
 int /*<<< orphan*/ * d2i_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dup_bio_in (int) ; 
 scalar_t__ get_ui_method () ; 
 int /*<<< orphan*/  load_pkcs12 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  unbuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_password_callback ; 

EVP_PKEY *load_key(const char *file, int format, int maybe_stdin,
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
            if (ENGINE_init(e)) {
                pkey = ENGINE_load_private_key(e, file,
                                               (UI_METHOD *)get_ui_method(),
                                               &cb_data);
                ENGINE_finish(e);
            }
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
        pkey = d2i_PrivateKey_bio(key, NULL);
    } else if (format == FORMAT_PEM) {
        pkey = PEM_read_bio_PrivateKey(key, NULL, wrap_password_callback, &cb_data);
    } else if (format == FORMAT_PKCS12) {
        if (!load_pkcs12(key, key_descrip, wrap_password_callback, &cb_data,
                         &pkey, NULL, NULL))
            goto end;
#if !defined(OPENSSL_NO_RSA) && !defined(OPENSSL_NO_DSA) && !defined (OPENSSL_NO_RC4)
    } else if (format == FORMAT_MSBLOB) {
        pkey = b2i_PrivateKey_bio(key);
    } else if (format == FORMAT_PVK) {
        pkey = b2i_PVK_bio(key, wrap_password_callback, &cb_data);
#endif
    } else {
        BIO_printf(bio_err, "bad input format specified for key file\n");
        goto end;
    }
 end:
    BIO_free(key);
    if (pkey == NULL) {
        BIO_printf(bio_err, "unable to load %s\n", key_descrip);
        ERR_print_errors(bio_err);
    }
    return pkey;
}