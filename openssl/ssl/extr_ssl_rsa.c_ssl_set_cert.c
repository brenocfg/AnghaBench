#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {TYPE_1__* pkeys; TYPE_1__* key; } ;
struct TYPE_4__ {int /*<<< orphan*/ * x509; int /*<<< orphan*/ * privatekey; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_2__ CERT ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_can_sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ EVP_PKEY_RSA ; 
 int /*<<< orphan*/  EVP_PKEY_copy_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_RSA (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int RSA_METHOD_FLAG_NO_CHECK ; 
 int RSA_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_F_SSL_SET_CERT ; 
 size_t SSL_PKEY_ECC ; 
 int /*<<< orphan*/  SSL_R_ECC_CERT_NOT_FOR_SIGNING ; 
 int /*<<< orphan*/  SSL_R_UNKNOWN_CERTIFICATE_TYPE ; 
 int /*<<< orphan*/  SSL_R_X509_LIB ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_check_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_cert_lookup_by_pkey (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int ssl_set_cert(CERT *c, X509 *x)
{
    EVP_PKEY *pkey;
    size_t i;

    pkey = X509_get0_pubkey(x);
    if (pkey == NULL) {
        SSLerr(SSL_F_SSL_SET_CERT, SSL_R_X509_LIB);
        return 0;
    }

    if (ssl_cert_lookup_by_pkey(pkey, &i) == NULL) {
        SSLerr(SSL_F_SSL_SET_CERT, SSL_R_UNKNOWN_CERTIFICATE_TYPE);
        return 0;
    }
#ifndef OPENSSL_NO_EC
    if (i == SSL_PKEY_ECC && !EC_KEY_can_sign(EVP_PKEY_get0_EC_KEY(pkey))) {
        SSLerr(SSL_F_SSL_SET_CERT, SSL_R_ECC_CERT_NOT_FOR_SIGNING);
        return 0;
    }
#endif
    if (c->pkeys[i].privatekey != NULL) {
        /*
         * The return code from EVP_PKEY_copy_parameters is deliberately
         * ignored. Some EVP_PKEY types cannot do this.
         */
        EVP_PKEY_copy_parameters(pkey, c->pkeys[i].privatekey);
        ERR_clear_error();

#ifndef OPENSSL_NO_RSA
        /*
         * Don't check the public/private key, this is mostly for smart
         * cards.
         */
        if (EVP_PKEY_id(c->pkeys[i].privatekey) == EVP_PKEY_RSA
            && RSA_flags(EVP_PKEY_get0_RSA(c->pkeys[i].privatekey)) &
            RSA_METHOD_FLAG_NO_CHECK) ;
        else
#endif                          /* OPENSSL_NO_RSA */
        if (!X509_check_private_key(x, c->pkeys[i].privatekey)) {
            /*
             * don't fail for a cert/key mismatch, just free current private
             * key (when switching to a different cert & key, first this
             * function should be used, then ssl_set_pkey
             */
            EVP_PKEY_free(c->pkeys[i].privatekey);
            c->pkeys[i].privatekey = NULL;
            /* clear error queue */
            ERR_clear_error();
        }
    }

    X509_free(c->pkeys[i].x509);
    X509_up_ref(x);
    c->pkeys[i].x509 = x;
    c->key = &(c->pkeys[i]);

    return 1;
}