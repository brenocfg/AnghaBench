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
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_DSA (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DSA *pkey_get_dsa(EVP_PKEY *key, DSA **dsa)
{
    DSA *dtmp;
    if (!key)
        return NULL;
    dtmp = EVP_PKEY_get1_DSA(key);
    EVP_PKEY_free(key);
    if (!dtmp)
        return NULL;
    if (dsa) {
        DSA_free(*dsa);
        *dsa = dtmp;
    }
    return dtmp;
}