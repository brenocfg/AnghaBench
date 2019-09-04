#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  default_passwd_callback_userdata; int /*<<< orphan*/  default_passwd_callback; } ;
typedef  TYPE_1__ SSL_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_read_filename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int ERR_R_ASN1_LIB ; 
 int ERR_R_BUF_LIB ; 
 int ERR_R_PEM_LIB ; 
 int ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_PrivateKey (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int SSL_FILETYPE_ASN1 ; 
 int SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE ; 
 int SSL_R_BAD_SSL_FILETYPE ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * d2i_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type)
{
    int j, ret = 0;
    BIO *in;
    EVP_PKEY *pkey = NULL;

    in = BIO_new(BIO_s_file());
    if (in == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, ERR_R_SYS_LIB);
        goto end;
    }
    if (type == SSL_FILETYPE_PEM) {
        j = ERR_R_PEM_LIB;
        pkey = PEM_read_bio_PrivateKey(in, NULL,
                                       ctx->default_passwd_callback,
                                       ctx->default_passwd_callback_userdata);
    } else if (type == SSL_FILETYPE_ASN1) {
        j = ERR_R_ASN1_LIB;
        pkey = d2i_PrivateKey_bio(in, NULL);
    } else {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, SSL_R_BAD_SSL_FILETYPE);
        goto end;
    }
    if (pkey == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_FILE, j);
        goto end;
    }
    ret = SSL_CTX_use_PrivateKey(ctx, pkey);
    EVP_PKEY_free(pkey);
 end:
    BIO_free(in);
    return ret;
}