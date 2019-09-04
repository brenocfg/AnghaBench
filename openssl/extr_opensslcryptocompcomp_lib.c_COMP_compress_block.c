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
struct TYPE_6__ {int compress_in; int compress_out; TYPE_1__* meth; } ;
struct TYPE_5__ {int (* compress ) (TYPE_2__*,unsigned char*,int,unsigned char*,int) ;} ;
typedef  TYPE_2__ COMP_CTX ;

/* Variables and functions */
 int stub1 (TYPE_2__*,unsigned char*,int,unsigned char*,int) ; 

int COMP_compress_block(COMP_CTX *ctx, unsigned char *out, int olen,
                        unsigned char *in, int ilen)
{
    int ret;
    if (ctx->meth->compress == NULL) {
        return -1;
    }
    ret = ctx->meth->compress(ctx, out, olen, in, ilen);
    if (ret > 0) {
        ctx->compress_in += ilen;
        ctx->compress_out += ret;
    }
    return ret;
}