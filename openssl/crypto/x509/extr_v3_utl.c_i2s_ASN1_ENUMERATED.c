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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  ASN1_ENUMERATED ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_ENUMERATED_to_BN (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  X509V3_F_I2S_ASN1_ENUMERATED ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* bignum_to_string (int /*<<< orphan*/ *) ; 

char *i2s_ASN1_ENUMERATED(X509V3_EXT_METHOD *method, const ASN1_ENUMERATED *a)
{
    BIGNUM *bntmp = NULL;
    char *strtmp = NULL;

    if (!a)
        return NULL;
    if ((bntmp = ASN1_ENUMERATED_to_BN(a, NULL)) == NULL
        || (strtmp = bignum_to_string(bntmp)) == NULL)
        X509V3err(X509V3_F_I2S_ASN1_ENUMERATED, ERR_R_MALLOC_FAILURE);
    BN_free(bntmp);
    return strtmp;
}