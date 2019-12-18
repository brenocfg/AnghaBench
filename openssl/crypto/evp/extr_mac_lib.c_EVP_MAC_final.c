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
struct TYPE_6__ {int /*<<< orphan*/  data; TYPE_1__* meth; } ;
struct TYPE_5__ {int (* final ) (int /*<<< orphan*/ ,unsigned char*,size_t*,size_t) ;} ;
typedef  TYPE_2__ EVP_MAC_CTX ;

/* Variables and functions */
 int EVP_MAC_size (TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,size_t*,size_t) ; 

int EVP_MAC_final(EVP_MAC_CTX *ctx,
                  unsigned char *out, size_t *outl, size_t outsize)
{
    int l = EVP_MAC_size(ctx);

    if (l < 0)
        return 0;
    if (outl != NULL)
        *outl = l;
    if (out == NULL)
        return 1;
    return ctx->meth->final(ctx->data, out, outl, outsize);
}