#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t block_padding; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 size_t SSL3_RT_MAX_PLAIN_LENGTH ; 

int SSL_CTX_set_block_padding(SSL_CTX *ctx, size_t block_size)
{
    /* block size of 0 or 1 is basically no padding */
    if (block_size == 1)
        ctx->block_padding = 0;
    else if (block_size <= SSL3_RT_MAX_PLAIN_LENGTH)
        ctx->block_padding = block_size;
    else
        return 0;
    return 1;
}