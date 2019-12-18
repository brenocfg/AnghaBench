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
struct TYPE_4__ {int md_size; } ;
typedef  TYPE_1__ KECCAK1600_CTX ;

/* Variables and functions */
 int sha3_init (TYPE_1__*,unsigned char,size_t) ; 

int keccak_kmac_init(KECCAK1600_CTX *ctx, unsigned char pad, size_t bitlen)
{
    int ret = sha3_init(ctx, pad, bitlen);

    if (ret)
        ctx->md_size *= 2;
    return ret;
}