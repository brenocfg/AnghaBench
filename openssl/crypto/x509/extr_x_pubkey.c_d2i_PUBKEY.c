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
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_PUBKEY_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509_PUBKEY (int /*<<< orphan*/ *,unsigned char const**,long) ; 

EVP_PKEY *d2i_PUBKEY(EVP_PKEY **a, const unsigned char **pp, long length)
{
    X509_PUBKEY *xpk;
    EVP_PKEY *pktmp;
    const unsigned char *q;

    q = *pp;
    xpk = d2i_X509_PUBKEY(NULL, &q, length);
    if (xpk == NULL)
        return NULL;
    pktmp = X509_PUBKEY_get(xpk);
    X509_PUBKEY_free(xpk);
    if (pktmp == NULL)
        return NULL;
    *pp = q;
    if (a != NULL) {
        EVP_PKEY_free(*a);
        *a = pktmp;
    }
    return pktmp;
}