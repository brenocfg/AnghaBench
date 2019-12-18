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
struct TYPE_3__ {scalar_t__ expected; int /*<<< orphan*/  src_string; int /*<<< orphan*/  tgt_string; } ;
typedef  TYPE_1__ CMP_ASN_TEST_FIXTURE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TEST_int_eq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_asn1_octet_string_set1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_CMP_ASN1_OCTET_STRING_set1_test(CMP_ASN_TEST_FIXTURE *
                                                   fixture)
{
    if (!TEST_int_eq(fixture->expected,
                     ossl_cmp_asn1_octet_string_set1(&fixture->tgt_string,
                                                     fixture->src_string)))
        return 0;
    if (fixture->expected != 0)
        return TEST_int_eq(0, ASN1_OCTET_STRING_cmp(fixture->tgt_string,
                                                    fixture->src_string));
    return 1;
}