#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* digest; } ;
struct TYPE_5__ {int (* md_ctrl ) (TYPE_2__*,int,int,void*) ;} ;
typedef  TYPE_2__ EVP_MD_CTX ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int,int,void*) ; 

int EVP_MD_CTX_ctrl(EVP_MD_CTX *ctx, int cmd, int p1, void *p2)
{
    if (ctx->digest && ctx->digest->md_ctrl) {
        int ret = ctx->digest->md_ctrl(ctx, cmd, p1, p2);
        if (ret <= 0)
            return 0;
        return 1;
    }
    return 0;
}