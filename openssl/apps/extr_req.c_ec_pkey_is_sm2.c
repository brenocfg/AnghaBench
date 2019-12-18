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
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 scalar_t__ EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_EC ; 
 scalar_t__ EVP_PKEY_SM2 ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 scalar_t__ NID_sm2 ; 

__attribute__((used)) static int ec_pkey_is_sm2(EVP_PKEY *pkey)
{
    EC_KEY *eckey = NULL;
    const EC_GROUP *group = NULL;

    if (EVP_PKEY_id(pkey) == EVP_PKEY_SM2)
        return 1;
    if (EVP_PKEY_id(pkey) == EVP_PKEY_EC
            && (eckey = EVP_PKEY_get0_EC_KEY(pkey)) != NULL
            && (group = EC_KEY_get0_group(eckey)) != NULL
            && EC_GROUP_get_curve_name(group) == NID_sm2)
        return 1;
    return 0;
}