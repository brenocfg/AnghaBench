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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_RSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PUBKEY (int /*<<< orphan*/ *,unsigned char const**,long) ; 

RSA *d2i_RSA_PUBKEY(RSA **a, const unsigned char **pp, long length)
{
    EVP_PKEY *pkey;
    RSA *key;
    const unsigned char *q;

    q = *pp;
    pkey = d2i_PUBKEY(NULL, &q, length);
    if (pkey == NULL)
        return NULL;
    key = EVP_PKEY_get1_RSA(pkey);
    EVP_PKEY_free(pkey);
    if (key == NULL)
        return NULL;
    *pp = q;
    if (a != NULL) {
        RSA_free(*a);
        *a = key;
    }
    return key;
}