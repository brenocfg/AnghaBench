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
struct TYPE_3__ {int /*<<< orphan*/ * tmpmd; int /*<<< orphan*/ * tmpengine; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int HMAC_Init_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hmac_init(EVP_MAC_IMPL *hctx)
{
    int rv = 1;

    /* HMAC_Init_ex doesn't tolerate all zero params, so we must be careful */
    if (hctx->tmpmd != NULL)
        rv = HMAC_Init_ex(hctx->ctx, NULL, 0, hctx->tmpmd,
                          (ENGINE * )hctx->tmpengine);
    hctx->tmpengine = NULL;
    hctx->tmpmd = NULL;
    return rv;
}