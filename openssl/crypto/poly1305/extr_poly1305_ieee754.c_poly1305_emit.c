#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* h; } ;
typedef  TYPE_2__ poly1305_internal ;
struct TYPE_3__ {int u; } ;

/* Variables and functions */
 int /*<<< orphan*/  U32TO8 (unsigned char*,int) ; 

void poly1305_emit(void *ctx, unsigned char mac[16], const u32 nonce[4])
{
    poly1305_internal *st = (poly1305_internal *) ctx;
    u64 h0, h1, h2, h3, h4;
    u32 g0, g1, g2, g3, g4;
    u64 t;
    u32 mask;

    /*
     * thanks to bias masking exponent gives integer result
     */
    h0 = st->h[0].u & 0x000fffffffffffffULL;
    h1 = st->h[1].u & 0x000fffffffffffffULL;
    h2 = st->h[2].u & 0x000fffffffffffffULL;
    h3 = st->h[3].u & 0x000fffffffffffffULL;

    /*
     * can be partially reduced, so reduce...
     */
    h4 = h3>>32; h3 &= 0xffffffffU;
    g4 = h4&-4;
    h4 &= 3;
    g4 += g4>>2;

    h0 += g4;
    h1 += h0>>32; h0 &= 0xffffffffU;
    h2 += h1>>32; h1 &= 0xffffffffU;
    h3 += h2>>32; h2 &= 0xffffffffU;

    /* compute h + -p */
    g0 = (u32)(t = h0 + 5);
    g1 = (u32)(t = h1 + (t >> 32));
    g2 = (u32)(t = h2 + (t >> 32));
    g3 = (u32)(t = h3 + (t >> 32));
    g4 = h4 + (u32)(t >> 32);

    /* if there was carry, select g0-g3 */
    mask = 0 - (g4 >> 2);
    g0 &= mask;
    g1 &= mask;
    g2 &= mask;
    g3 &= mask;
    mask = ~mask;
    g0 |= (h0 & mask);
    g1 |= (h1 & mask);
    g2 |= (h2 & mask);
    g3 |= (h3 & mask);

    /* mac = (h + nonce) % (2^128) */
    g0 = (u32)(t = (u64)g0 + nonce[0]);
    g1 = (u32)(t = (u64)g1 + (t >> 32) + nonce[1]);
    g2 = (u32)(t = (u64)g2 + (t >> 32) + nonce[2]);
    g3 = (u32)(t = (u64)g3 + (t >> 32) + nonce[3]);

    U32TO8(mac + 0, g0);
    U32TO8(mac + 4, g1);
    U32TO8(mac + 8, g2);
    U32TO8(mac + 12, g3);
}