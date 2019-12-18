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
struct TYPE_3__ {int /*<<< orphan*/  generalInfo; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;
typedef  int /*<<< orphan*/  OSSL_CMP_ITAV ;

/* Variables and functions */
 int OSSL_CMP_ITAV_push0_stack_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int ossl_cmp_hdr_generalInfo_push0_item(OSSL_CMP_PKIHEADER *hdr,
                                        OSSL_CMP_ITAV *itav)
{
    if (!ossl_assert(hdr != NULL && itav != NULL))
        return 0;
    return OSSL_CMP_ITAV_push0_stack_item(&hdr->generalInfo, itav);
}