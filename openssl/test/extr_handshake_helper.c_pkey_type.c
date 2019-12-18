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
 int EC_GROUP_get_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_EC ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_type(EVP_PKEY *pkey)
{
    int nid = EVP_PKEY_id(pkey);

#ifndef OPENSSL_NO_EC
    if (nid == EVP_PKEY_EC) {
        const EC_KEY *ec = EVP_PKEY_get0_EC_KEY(pkey);
        return EC_GROUP_get_curve_name(EC_KEY_get0_group(ec));
    }
#endif
    return nid;
}