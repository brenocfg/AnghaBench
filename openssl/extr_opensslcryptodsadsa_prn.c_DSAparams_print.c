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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int EVP_PKEY_print_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_set1_DSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int DSAparams_print(BIO *bp, const DSA *x)
{
    EVP_PKEY *pk;
    int ret;
    pk = EVP_PKEY_new();
    if (pk == NULL || !EVP_PKEY_set1_DSA(pk, (DSA *)x))
        return 0;
    ret = EVP_PKEY_print_params(bp, pk, 4, NULL);
    EVP_PKEY_free(pk);
    return ret;
}