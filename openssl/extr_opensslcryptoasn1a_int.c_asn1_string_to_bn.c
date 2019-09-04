#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_STRING_TO_BN ; 
 int /*<<< orphan*/  ASN1_R_BN_LIB ; 
 int /*<<< orphan*/  ASN1_R_WRONG_INTEGER_TYPE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int) ; 
 int V_ASN1_NEG ; 

__attribute__((used)) static BIGNUM *asn1_string_to_bn(const ASN1_INTEGER *ai, BIGNUM *bn,
                                 int itype)
{
    BIGNUM *ret;

    if ((ai->type & ~V_ASN1_NEG) != itype) {
        ASN1err(ASN1_F_ASN1_STRING_TO_BN, ASN1_R_WRONG_INTEGER_TYPE);
        return NULL;
    }

    ret = BN_bin2bn(ai->data, ai->length, bn);
    if (ret == NULL) {
        ASN1err(ASN1_F_ASN1_STRING_TO_BN, ASN1_R_BN_LIB);
        return NULL;
    }
    if (ai->type & V_ASN1_NEG)
        BN_set_negative(ret, 1);
    return ret;
}