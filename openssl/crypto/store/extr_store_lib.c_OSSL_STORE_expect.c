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
struct TYPE_5__ {int expected_type; int /*<<< orphan*/  loader_ctx; TYPE_1__* loader; scalar_t__ loading; } ;
struct TYPE_4__ {int (* expect ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__ OSSL_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_EXPECT ; 
 int /*<<< orphan*/  OSSL_STORE_R_LOADING_STARTED ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int OSSL_STORE_expect(OSSL_STORE_CTX *ctx, int expected_type)
{
    if (ctx->loading) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_EXPECT,
                      OSSL_STORE_R_LOADING_STARTED);
        return 0;
    }

    ctx->expected_type = expected_type;
    if (ctx->loader->expect != NULL)
        return ctx->loader->expect(ctx->loader_ctx, expected_type);
    return 1;
}