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
typedef  int uint64_t ;
struct TYPE_3__ {int total_inlen; int v0; int v1; int v2; int v3; scalar_t__ hash_size; int len; int crounds; int drounds; int /*<<< orphan*/ * leavings; } ;
typedef  TYPE_1__ SIPHASH ;

/* Variables and functions */
 scalar_t__ SIPHASH_MAX_DIGEST_SIZE ; 
 scalar_t__ SIPHASH_MIN_DIGEST_SIZE ; 
 int /*<<< orphan*/  SIPROUND ; 
 int /*<<< orphan*/  U64TO8_LE (unsigned char*,int) ; 

int SipHash_Final(SIPHASH *ctx, unsigned char *out, size_t outlen)
{
    /* finalize hash */
    int i;
    uint64_t b = ctx->total_inlen << 56;
    uint64_t v0 = ctx->v0;
    uint64_t v1 = ctx->v1;
    uint64_t v2 = ctx->v2;
    uint64_t v3 = ctx->v3;

    if (outlen != (size_t)ctx->hash_size)
        return 0;

    switch (ctx->len) {
    case 7:
        b |= ((uint64_t)ctx->leavings[6]) << 48;
        /* fall thru */
    case 6:
        b |= ((uint64_t)ctx->leavings[5]) << 40;
        /* fall thru */
    case 5:
        b |= ((uint64_t)ctx->leavings[4]) << 32;
        /* fall thru */
    case 4:
        b |= ((uint64_t)ctx->leavings[3]) << 24;
        /* fall thru */
    case 3:
        b |= ((uint64_t)ctx->leavings[2]) << 16;
        /* fall thru */
    case 2:
        b |= ((uint64_t)ctx->leavings[1]) <<  8;
        /* fall thru */
    case 1:
        b |= ((uint64_t)ctx->leavings[0]);
    case 0:
        break;
    }

    v3 ^= b;
    for (i = 0; i < ctx->crounds; ++i)
        SIPROUND;
    v0 ^= b;
    if (ctx->hash_size == SIPHASH_MAX_DIGEST_SIZE)
        v2 ^= 0xee;
    else
        v2 ^= 0xff;
    for (i = 0; i < ctx->drounds; ++i)
        SIPROUND;
    b = v0 ^ v1 ^ v2  ^ v3;
    U64TO8_LE(out, b);
    if (ctx->hash_size == SIPHASH_MIN_DIGEST_SIZE)
        return 1;
    v1 ^= 0xdd;
    for (i = 0; i < ctx->drounds; ++i)
        SIPROUND;
    b = v0 ^ v1 ^ v2  ^ v3;
    U64TO8_LE(out + 8, b);
    return 1;
}