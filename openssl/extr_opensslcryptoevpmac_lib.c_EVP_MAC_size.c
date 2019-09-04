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
struct TYPE_5__ {int /*<<< orphan*/ * data; TYPE_1__* meth; } ;
struct TYPE_4__ {size_t (* size ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EVP_MAC_CTX ;

/* Variables and functions */
 size_t stub1 (int /*<<< orphan*/ *) ; 

size_t EVP_MAC_size(EVP_MAC_CTX *ctx)
{
    if (ctx->data != NULL)
        return ctx->meth->size(ctx->data);
    /* If the MAC hasn't been initialized yet, we return zero */
    return 0;
}