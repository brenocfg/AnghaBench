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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int /*<<< orphan*/  loader_ctx; TYPE_1__* loader; } ;
struct TYPE_4__ {int (* ctrl ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ OSSL_STORE_CTX ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int OSSL_STORE_vctrl(OSSL_STORE_CTX *ctx, int cmd, va_list args)
{
    if (ctx->loader->ctrl != NULL)
        return ctx->loader->ctrl(ctx->loader_ctx, cmd, args);
    return 0;
}