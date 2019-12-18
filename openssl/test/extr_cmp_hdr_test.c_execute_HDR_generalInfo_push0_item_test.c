#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  generalInfo; } ;
struct TYPE_4__ {TYPE_2__* hdr; } ;
typedef  int /*<<< orphan*/  OSSL_CMP_ITAV ;
typedef  TYPE_1__ CMP_HDR_TEST_FIXTURE ;

/* Variables and functions */
 int /*<<< orphan*/ * OSSL_CMP_ITAV_new () ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_generalInfo_push0_item (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_OSSL_CMP_ITAV_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
execute_HDR_generalInfo_push0_item_test(CMP_HDR_TEST_FIXTURE *fixture)
{
    OSSL_CMP_ITAV *itav = OSSL_CMP_ITAV_new();

    if (!TEST_ptr(itav))
        return 0;

    if (!TEST_int_eq(
            ossl_cmp_hdr_generalInfo_push0_item(fixture->hdr, itav), 1))
        return 0;
    if (!TEST_true(itav == sk_OSSL_CMP_ITAV_value(
            fixture->hdr->generalInfo, 0)))
        return 0;

    return 1;
}