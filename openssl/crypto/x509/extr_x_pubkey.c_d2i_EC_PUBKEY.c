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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PUBKEY (int /*<<< orphan*/ *,unsigned char const**,long) ; 

EC_KEY *d2i_EC_PUBKEY(EC_KEY **a, const unsigned char **pp, long length)
{
    EVP_PKEY *pkey;
    EC_KEY *key;
    const unsigned char *q;

    q = *pp;
    pkey = d2i_PUBKEY(NULL, &q, length);
    if (pkey == NULL)
        return NULL;
    key = EVP_PKEY_get1_EC_KEY(pkey);
    EVP_PKEY_free(pkey);
    if (key == NULL)
        return NULL;
    *pp = q;
    if (a != NULL) {
        EC_KEY_free(*a);
        *a = key;
    }
    return key;
}