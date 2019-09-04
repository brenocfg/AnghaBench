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
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int SipHash_Final (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 size_t siphash_size (TYPE_1__*) ; 

__attribute__((used)) static int siphash_final(EVP_MAC_IMPL *sctx, unsigned char *out)
{
    size_t hlen = siphash_size(sctx);

    return SipHash_Final(&sctx->ctx, out, hlen);
}