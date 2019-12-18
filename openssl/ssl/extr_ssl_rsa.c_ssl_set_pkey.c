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
struct TYPE_5__ {TYPE_1__* pkeys; TYPE_1__* key; } ;
struct TYPE_4__ {int /*<<< orphan*/ * privatekey; int /*<<< orphan*/ * x509; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_2__ CERT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ EVP_PKEY_RSA ; 
 int /*<<< orphan*/  EVP_PKEY_copy_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_RSA (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_up_ref (int /*<<< orphan*/ *) ; 
 int RSA_METHOD_FLAG_NO_CHECK ; 
 int RSA_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_F_SSL_SET_PKEY ; 
 int /*<<< orphan*/  SSL_R_UNKNOWN_CERTIFICATE_TYPE ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_check_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_cert_lookup_by_pkey (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int ssl_set_pkey(CERT *c, EVP_PKEY *pkey)
{
    size_t i;

    if (ssl_cert_lookup_by_pkey(pkey, &i) == NULL) {
        SSLerr(SSL_F_SSL_SET_PKEY, SSL_R_UNKNOWN_CERTIFICATE_TYPE);
        return 0;
    }

    if (c->pkeys[i].x509 != NULL) {
        EVP_PKEY *pktmp;
        pktmp = X509_get0_pubkey(c->pkeys[i].x509);
        if (pktmp == NULL) {
            SSLerr(SSL_F_SSL_SET_PKEY, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        /*
         * The return code from EVP_PKEY_copy_parameters is deliberately
         * ignored. Some EVP_PKEY types cannot do this.
         */
        EVP_PKEY_copy_parameters(pktmp, pkey);
        ERR_clear_error();

#ifndef OPENSSL_NO_RSA
        /*
         * Don't check the public/private key, this is mostly for smart
         * cards.
         */
        if (EVP_PKEY_id(pkey) == EVP_PKEY_RSA
            && RSA_flags(EVP_PKEY_get0_RSA(pkey)) & RSA_METHOD_FLAG_NO_CHECK) ;
        else
#endif
        if (!X509_check_private_key(c->pkeys[i].x509, pkey)) {
            X509_free(c->pkeys[i].x509);
            c->pkeys[i].x509 = NULL;
            return 0;
        }
    }

    EVP_PKEY_free(c->pkeys[i].privatekey);
    EVP_PKEY_up_ref(pkey);
    c->pkeys[i].privatekey = pkey;
    c->key = &c->pkeys[i];
    return 1;
}