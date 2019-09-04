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
struct TYPE_6__ {int /*<<< orphan*/  loader_ctx; TYPE_1__* loader; } ;
struct TYPE_5__ {int (* close ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ OSSL_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int OSSL_STORE_close(OSSL_STORE_CTX *ctx)
{
    int loader_ret = ctx->loader->close(ctx->loader_ctx);

    OPENSSL_free(ctx);
    return loader_ret;
}