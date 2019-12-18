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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int u128 ;
struct TYPE_2__ {int* r; int* s; int* h; } ;
typedef  TYPE_1__ poly1305_internal ;

/* Variables and functions */
 size_t POLY1305_BLOCK_SIZE ; 
 int U8TOU64 (unsigned char const*) ; 

void poly1305_blocks(void *ctx, const unsigned char *inp, size_t len,
                     u32 padbit)
{
    poly1305_internal *st = (poly1305_internal *)ctx;
    u64 r0, r1, r2;
    u64 s1, s2;
    u64 h0, h1, h2, c;
    u128 d0, d1, d2;
    u64 pad = (u64)padbit << 40;

    r0 = st->r[0];
    r1 = st->r[1];
    r2 = st->r[2];

    s1 = st->s[0];
    s2 = st->s[1];

    h0 = st->h[0];
    h1 = st->h[1];
    h2 = st->h[2];

    while (len >= POLY1305_BLOCK_SIZE) {
        u64 m0, m1;

        m0 = U8TOU64(inp + 0);
        m1 = U8TOU64(inp + 8);

        /* h += m[i], m[i] is broken to 44-bit digits */
        h0 += m0 & 0x0fffffffffff;
        h1 += ((m0 >> 44) | (m1 << 20))  & 0x0fffffffffff;
        h2 +=  (m1 >> 24) + pad;

        /* h *= r "%" p, where "%" stands for "partial remainder" */
        d0 = ((u128)h0 * r0) + ((u128)h1 * s2) + ((u128)h2 * s1);
        d1 = ((u128)h0 * r1) + ((u128)h1 * r0) + ((u128)h2 * s2);
        d2 = ((u128)h0 * r2) + ((u128)h1 * r1) + ((u128)h2 * r0);

        /* "lazy" reduction step */
        h0 = (u64)d0 & 0x0fffffffffff;
        h1 = (u64)(d1 += (u64)(d0 >> 44)) & 0x0fffffffffff;
        h2 = (u64)(d2 += (u64)(d1 >> 44)) & 0x03ffffffffff; /* last 42 bits */

        c = (d2 >> 42);
        h0 += c + (c << 2);

        inp += POLY1305_BLOCK_SIZE;
        len -= POLY1305_BLOCK_SIZE;
    }

    st->h[0] = h0;
    st->h[1] = h1;
    st->h[2] = h2;
}