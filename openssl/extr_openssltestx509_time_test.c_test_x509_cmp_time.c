#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_6__ {int /*<<< orphan*/  expected; int /*<<< orphan*/  cmp_time; scalar_t__ data; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {unsigned char* data; scalar_t__ flags; int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_info (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int /*<<< orphan*/ ) ; 
 int X509_cmp_time (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 TYPE_2__* x509_cmp_tests ; 

__attribute__((used)) static int test_x509_cmp_time(int idx)
{
    ASN1_TIME t;
    int result;

    memset(&t, 0, sizeof(t));
    t.type = x509_cmp_tests[idx].type;
    t.data = (unsigned char*)(x509_cmp_tests[idx].data);
    t.length = strlen(x509_cmp_tests[idx].data);
    t.flags = 0;

    result = X509_cmp_time(&t, &x509_cmp_tests[idx].cmp_time);
    if (!TEST_int_eq(result, x509_cmp_tests[idx].expected)) {
        TEST_info("test_x509_cmp_time(%d) failed: expected %d, got %d\n",
                idx, x509_cmp_tests[idx].expected, result);
        return 0;
    }
    return 1;
}