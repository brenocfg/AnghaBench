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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_nid2group_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t tls1_get_group_id(EVP_PKEY *pkey)
{
    EC_KEY *ec = EVP_PKEY_get0_EC_KEY(pkey);
    const EC_GROUP *grp;

    if (ec == NULL)
        return 0;
    grp = EC_KEY_get0_group(ec);
    return tls1_nid2group_id(EC_GROUP_get_curve_name(grp));
}