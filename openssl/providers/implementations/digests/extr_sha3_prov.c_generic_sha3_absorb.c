#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  block_size; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ KECCAK1600_CTX ;

/* Variables and functions */
 size_t SHA3_absorb (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t generic_sha3_absorb(void *vctx, const void *inp, size_t len)
{
    KECCAK1600_CTX *ctx = vctx;

    return SHA3_absorb(ctx->A, inp, len, ctx->block_size);
}