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
struct compare_testdata {int /*<<< orphan*/  result; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TIME_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct compare_testdata* tbl_compare_testdata ; 

__attribute__((used)) static int test_table_compare(int idx)
{
    struct compare_testdata *td = &tbl_compare_testdata[idx];

    return TEST_int_eq(ASN1_TIME_compare(&td->t1, &td->t2), td->result);
}