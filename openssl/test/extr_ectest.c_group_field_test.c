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
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get0_field (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_secp521r1 ; 
 int /*<<< orphan*/  NID_sect163r2 ; 

__attribute__((used)) static int group_field_test(void)
{
    int r = 1;
    BIGNUM *secp521r1_field = NULL;
    BIGNUM *sect163r2_field = NULL;
    EC_GROUP *secp521r1_group = NULL;
    EC_GROUP *sect163r2_group = NULL;

    BN_hex2bn(&secp521r1_field,
                "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
                "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
                "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
                "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
                "FFFF");


    BN_hex2bn(&sect163r2_field,
                "08000000000000000000000000000000"
                "00000000C9");

    secp521r1_group = EC_GROUP_new_by_curve_name(NID_secp521r1);
    if (BN_cmp(secp521r1_field, EC_GROUP_get0_field(secp521r1_group)))
      r = 0;

    # ifndef OPENSSL_NO_EC2M
    sect163r2_group = EC_GROUP_new_by_curve_name(NID_sect163r2);
    if (BN_cmp(sect163r2_field, EC_GROUP_get0_field(sect163r2_group)))
      r = 0;
    # endif

    EC_GROUP_free(secp521r1_group);
    EC_GROUP_free(sect163r2_group);
    BN_free(secp521r1_field);
    BN_free(sect163r2_field);
    return r;
}