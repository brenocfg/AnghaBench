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
struct TYPE_3__ {int /*<<< orphan*/  geninfo_ITAVs; } ;
typedef  int /*<<< orphan*/  OSSL_CMP_ITAV ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OSSL_CMP_ITAV_push0_stack_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OSSL_CMP_CTX_push0_geninfo_ITAV(OSSL_CMP_CTX *ctx, OSSL_CMP_ITAV *itav)
{
    if (ctx == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    return OSSL_CMP_ITAV_push0_stack_item(&ctx->geninfo_ITAVs, itav);
}