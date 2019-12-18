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
struct TYPE_3__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ CMP_HDR_TEST_FIXTURE ;

/* Variables and functions */
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_check_implicitConfirm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_set_implicitConfirm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
execute_HDR_set_and_check_implicitConfirm_test(CMP_HDR_TEST_FIXTURE
                                               * fixture)
{
    return TEST_false(ossl_cmp_hdr_check_implicitConfirm(fixture->hdr))
        && TEST_true(ossl_cmp_hdr_set_implicitConfirm(fixture->hdr))
        && TEST_true(ossl_cmp_hdr_check_implicitConfirm(fixture->hdr));
}