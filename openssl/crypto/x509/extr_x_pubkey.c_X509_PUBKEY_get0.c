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
struct TYPE_4__ {int /*<<< orphan*/ * pkey; int /*<<< orphan*/ * public_key; } ;
typedef  TYPE_1__ X509_PUBKEY ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_F_X509_PUBKEY_GET0 ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x509_pubkey_decode (int /*<<< orphan*/ **,TYPE_1__*) ; 

EVP_PKEY *X509_PUBKEY_get0(X509_PUBKEY *key)
{
    EVP_PKEY *ret = NULL;

    if (key == NULL || key->public_key == NULL)
        return NULL;

    if (key->pkey != NULL)
        return key->pkey;

    /*
     * When the key ASN.1 is initially parsed an attempt is made to
     * decode the public key and cache the EVP_PKEY structure. If this
     * operation fails the cached value will be NULL. Parsing continues
     * to allow parsing of unknown key types or unsupported forms.
     * We repeat the decode operation so the appropriate errors are left
     * in the queue.
     */
    x509_pubkey_decode(&ret, key);
    /* If decode doesn't fail something bad happened */
    if (ret != NULL) {
        X509err(X509_F_X509_PUBKEY_GET0, ERR_R_INTERNAL_ERROR);
        EVP_PKEY_free(ret);
    }

    return NULL;
}