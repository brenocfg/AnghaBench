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
struct TYPE_2__ {int expected; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_ASN_TEST_FIXTURE ; 
 int /*<<< orphan*/  EXECUTE_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP_TEST_FIXTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_cmp_asn1_get_int_test ; 
 TYPE_1__* fixture ; 
 int result ; 
 int /*<<< orphan*/  set_up ; 
 int /*<<< orphan*/  tear_down ; 

__attribute__((used)) static int test_cmp_asn1_get_int(void)
{
    SETUP_TEST_FIXTURE(CMP_ASN_TEST_FIXTURE, set_up);
    fixture->expected = 1;
    EXECUTE_TEST(execute_cmp_asn1_get_int_test, tear_down);
    return result;
}