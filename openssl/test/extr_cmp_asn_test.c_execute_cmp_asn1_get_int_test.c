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
typedef  int /*<<< orphan*/  CMP_ASN_TEST_FIXTURE ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_asn1_get_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int execute_cmp_asn1_get_int_test(CMP_ASN_TEST_FIXTURE *
                                                   fixture)
{
    ASN1_INTEGER *asn1integer = ASN1_INTEGER_new();
    ASN1_INTEGER_set(asn1integer, 77);
    if (!TEST_int_eq(77, ossl_cmp_asn1_get_int(asn1integer)))
        return 0;
    ASN1_INTEGER_free(asn1integer);
    return 1;
}