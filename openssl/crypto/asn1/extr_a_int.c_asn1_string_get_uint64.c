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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_STRING_GET_UINT64 ; 
 int /*<<< orphan*/  ASN1_R_ILLEGAL_NEGATIVE_VALUE ; 
 int /*<<< orphan*/  ASN1_R_WRONG_INTEGER_TYPE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int V_ASN1_NEG ; 
 int asn1_get_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asn1_string_get_uint64(uint64_t *pr, const ASN1_STRING *a,
                                  int itype)
{
    if (a == NULL) {
        ASN1err(ASN1_F_ASN1_STRING_GET_UINT64, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if ((a->type & ~V_ASN1_NEG) != itype) {
        ASN1err(ASN1_F_ASN1_STRING_GET_UINT64, ASN1_R_WRONG_INTEGER_TYPE);
        return 0;
    }
    if (a->type & V_ASN1_NEG) {
        ASN1err(ASN1_F_ASN1_STRING_GET_UINT64, ASN1_R_ILLEGAL_NEGATIVE_VALUE);
        return 0;
    }
    return asn1_get_uint64(pr, a->data, a->length);
}