#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tm {int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_yday; } ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_2__ {int /*<<< orphan*/  wd; int /*<<< orphan*/  yd; int /*<<< orphan*/  d; int /*<<< orphan*/  m; int /*<<< orphan*/  y; } ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_TIME_new () ; 
 int /*<<< orphan*/  ASN1_TIME_set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ASN1_TIME_to_tm (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* day_of_week_tests ; 

__attribute__((used)) static int test_days(int n)
{
    char d[16];
    ASN1_TIME *a = NULL;
    struct tm t;
    int r;

    BIO_snprintf(d, sizeof(d), "%04d%02d%02d050505Z",
                 day_of_week_tests[n].y, day_of_week_tests[n].m,
                 day_of_week_tests[n].d);

    if (!TEST_ptr(a = ASN1_TIME_new()))
        return 0;

    r = TEST_true(ASN1_TIME_set_string(a, d))
        && TEST_true(ASN1_TIME_to_tm(a, &t))
        && TEST_int_eq(t.tm_yday, day_of_week_tests[n].yd)
        && TEST_int_eq(t.tm_wday, day_of_week_tests[n].wd);

    ASN1_TIME_free(a);
    return r;
}