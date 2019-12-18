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
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_EC ; 
 int /*<<< orphan*/  EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int NID_X9_62_prime256v1 ; 
 int NID_ecdsa_with_SHA256 ; 
 int NID_ecdsa_with_SHA384 ; 
 int NID_secp384r1 ; 
 int X509_V_ERR_SUITE_B_INVALID_ALGORITHM ; 
 int X509_V_ERR_SUITE_B_INVALID_CURVE ; 
 int X509_V_ERR_SUITE_B_INVALID_SIGNATURE_ALGORITHM ; 
 int X509_V_ERR_SUITE_B_LOS_NOT_ALLOWED ; 
 unsigned long X509_V_FLAG_SUITEB_128_LOS_ONLY ; 
 unsigned long X509_V_FLAG_SUITEB_192_LOS ; 
 int X509_V_OK ; 

__attribute__((used)) static int check_suite_b(EVP_PKEY *pkey, int sign_nid, unsigned long *pflags)
{
    const EC_GROUP *grp = NULL;
    int curve_nid;
    if (pkey && EVP_PKEY_id(pkey) == EVP_PKEY_EC)
        grp = EC_KEY_get0_group(EVP_PKEY_get0_EC_KEY(pkey));
    if (!grp)
        return X509_V_ERR_SUITE_B_INVALID_ALGORITHM;
    curve_nid = EC_GROUP_get_curve_name(grp);
    /* Check curve is consistent with LOS */
    if (curve_nid == NID_secp384r1) { /* P-384 */
        /*
         * Check signature algorithm is consistent with curve.
         */
        if (sign_nid != -1 && sign_nid != NID_ecdsa_with_SHA384)
            return X509_V_ERR_SUITE_B_INVALID_SIGNATURE_ALGORITHM;
        if (!(*pflags & X509_V_FLAG_SUITEB_192_LOS))
            return X509_V_ERR_SUITE_B_LOS_NOT_ALLOWED;
        /* If we encounter P-384 we cannot use P-256 later */
        *pflags &= ~X509_V_FLAG_SUITEB_128_LOS_ONLY;
    } else if (curve_nid == NID_X9_62_prime256v1) { /* P-256 */
        if (sign_nid != -1 && sign_nid != NID_ecdsa_with_SHA256)
            return X509_V_ERR_SUITE_B_INVALID_SIGNATURE_ALGORITHM;
        if (!(*pflags & X509_V_FLAG_SUITEB_128_LOS_ONLY))
            return X509_V_ERR_SUITE_B_LOS_NOT_ALLOWED;
    } else
        return X509_V_ERR_SUITE_B_INVALID_CURVE;

    return X509_V_OK;
}