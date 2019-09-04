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
struct TYPE_3__ {scalar_t__ fail; size_t (* get_entropy ) (int /*<<< orphan*/ *,unsigned char**,int,size_t,size_t,int) ;int /*<<< orphan*/  reseed_count; } ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  TYPE_1__ HOOK_CTX ;

/* Variables and functions */
 TYPE_1__* get_hook_ctx (int /*<<< orphan*/ *) ; 
 size_t stub1 (int /*<<< orphan*/ *,unsigned char**,int,size_t,size_t,int) ; 

__attribute__((used)) static size_t get_entropy_hook(RAND_DRBG *drbg, unsigned char **pout,
                              int entropy, size_t min_len, size_t max_len,
                              int prediction_resistance)
{
    size_t ret;
    HOOK_CTX *ctx = get_hook_ctx(drbg);

    if (ctx->fail != 0)
        return 0;

    ret = ctx->get_entropy(drbg, pout, entropy, min_len, max_len,
                           prediction_resistance);

    if (ret != 0)
        ctx->reseed_count++;
    return ret;
}