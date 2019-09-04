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
struct TYPE_3__ {size_t hash_size; int v1; } ;
typedef  TYPE_1__ SIPHASH ;

/* Variables and functions */
 size_t SIPHASH_MAX_DIGEST_SIZE ; 
 size_t SIPHASH_MIN_DIGEST_SIZE ; 
 void* siphash_adjust_hash_size (size_t) ; 

int SipHash_set_hash_size(SIPHASH *ctx, size_t hash_size)
{
    hash_size = siphash_adjust_hash_size(hash_size);
    if (hash_size != SIPHASH_MIN_DIGEST_SIZE
        && hash_size != SIPHASH_MAX_DIGEST_SIZE)
        return 0;

    /*
     * It's possible that the key was set first.  If the hash size changes,
     * we need to adjust v1 (see SipHash_Init().
     */

    /* Start by adjusting the stored size, to make things easier */
    ctx->hash_size = siphash_adjust_hash_size(ctx->hash_size);

    /* Now, adjust ctx->v1 if the old and the new size differ */
    if ((size_t)ctx->hash_size != hash_size) {
        ctx->v1 ^= 0xee;
        ctx->hash_size = hash_size;
    }
    return 1;
}