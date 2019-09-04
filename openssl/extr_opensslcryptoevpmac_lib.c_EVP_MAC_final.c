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
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__* meth; } ;
struct TYPE_4__ {int (* size ) (int /*<<< orphan*/ ) ;int (* final ) (int /*<<< orphan*/ ,unsigned char*) ;} ;
typedef  TYPE_2__ EVP_MAC_CTX ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned char*) ; 

int EVP_MAC_final(EVP_MAC_CTX *ctx, unsigned char *out, size_t *poutlen)
{
    int l = ctx->meth->size(ctx->data);

    if (l < 0)
        return 0;
    if (poutlen != NULL)
        *poutlen = l;
    if (out == NULL)
        return 1;
    return ctx->meth->final(ctx->data, out);
}