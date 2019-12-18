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
struct TYPE_3__ {int status; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

int ossl_cmp_ctx_set_status(OSSL_CMP_CTX *ctx, int status)
{
    if (!ossl_assert(ctx != NULL))
        return 0;
    ctx->status = status;
    return 1;
}