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
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__* meth; } ;
struct TYPE_4__ {int (* ctrl ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ EVP_MAC_CTX ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int EVP_MAC_vctrl(EVP_MAC_CTX *ctx, int cmd, va_list args)
{
    int ok = 1;

    if (ctx == NULL || ctx->meth == NULL)
        return -2;

    switch (cmd) {
#if 0
    case ...:
        /* code */
        ok = 1;
        break;
#endif
    default:
        if (ctx->meth->ctrl != NULL)
            ok = ctx->meth->ctrl(ctx->data, cmd, args);
        else
            ok = -2;
        break;
    }

    return ok;
}