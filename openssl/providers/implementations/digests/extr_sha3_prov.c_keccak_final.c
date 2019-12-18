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
struct TYPE_4__ {int (* final ) (unsigned char*,TYPE_2__*) ;} ;
struct TYPE_5__ {size_t md_size; TYPE_1__ meth; } ;
typedef  TYPE_2__ KECCAK1600_CTX ;

/* Variables and functions */
 int stub1 (unsigned char*,TYPE_2__*) ; 

__attribute__((used)) static int keccak_final(void *vctx, unsigned char *out, size_t *outl,
                        size_t outsz)
{
    int ret = 1;
    KECCAK1600_CTX *ctx = vctx;

    if (outsz > 0)
        ret = ctx->meth.final(out, ctx);

    *outl = ctx->md_size;
    return ret;
}