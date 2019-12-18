#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct siphash_data_st {int /*<<< orphan*/  siphash; } ;

/* Variables and functions */
 size_t SipHash_hash_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t siphash_size(void *vmacctx)
{
    struct siphash_data_st *ctx = vmacctx;

    return SipHash_hash_size(&ctx->siphash);
}