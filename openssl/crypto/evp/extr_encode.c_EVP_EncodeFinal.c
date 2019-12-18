#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num; int flags; int /*<<< orphan*/  enc_data; } ;
typedef  TYPE_1__ EVP_ENCODE_CTX ;

/* Variables and functions */
 int EVP_ENCODE_CTX_NO_NEWLINES ; 
 unsigned int evp_encodeblock_int (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 

void EVP_EncodeFinal(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl)
{
    unsigned int ret = 0;

    if (ctx->num != 0) {
        ret = evp_encodeblock_int(ctx, out, ctx->enc_data, ctx->num);
        if ((ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) == 0)
            out[ret++] = '\n';
        out[ret] = '\0';
        ctx->num = 0;
    }
    *outl = ret;
}