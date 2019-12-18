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
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_get_pvno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_set_pvno (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int execute_HDR_set_get_pvno_test(CMP_HDR_TEST_FIXTURE *fixture)
{
    int pvno = 77;

    if (!TEST_int_eq(ossl_cmp_hdr_set_pvno(fixture->hdr, pvno), 1))
        return 0;
    if (!TEST_int_eq(ossl_cmp_hdr_get_pvno(fixture->hdr), pvno))
        return 0;
    return 1;
}