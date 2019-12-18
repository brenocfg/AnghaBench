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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_TIME_adj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_TIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int X509_cmp_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_x509_cmp_time_current(void)
{
    time_t now = time(NULL);
    /* Pick a day earlier and later, relative to any system clock. */
    ASN1_TIME *asn1_before = NULL, *asn1_after = NULL;
    int cmp_result, failed = 0;

    asn1_before = ASN1_TIME_adj(NULL, now, -1, 0);
    asn1_after = ASN1_TIME_adj(NULL, now, 1, 0);

    cmp_result  = X509_cmp_time(asn1_before, NULL);
    if (!TEST_int_eq(cmp_result, -1))
        failed = 1;

    cmp_result = X509_cmp_time(asn1_after, NULL);
    if (!TEST_int_eq(cmp_result, 1))
        failed = 1;

    ASN1_TIME_free(asn1_before);
    ASN1_TIME_free(asn1_after);

    return failed == 0;
}