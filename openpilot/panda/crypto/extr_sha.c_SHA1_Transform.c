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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int* state; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ SHA_CTX ;

/* Variables and functions */
 int rol (int,int) ; 

__attribute__((used)) static void SHA1_Transform(SHA_CTX* ctx) {
    uint32_t W[80];
    uint32_t A, B, C, D, E;
    uint8_t* p = ctx->buf;
    int t;

    for(t = 0; t < 16; ++t) {
        uint32_t tmp =  *p++ << 24;
        tmp |= *p++ << 16;
        tmp |= *p++ << 8;
        tmp |= *p++;
        W[t] = tmp;
    }

    for(; t < 80; t++) {
        W[t] = rol(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
    }

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];
    E = ctx->state[4];

    for(t = 0; t < 80; t++) {
        uint32_t tmp = rol(5,A) + E + W[t];

        if (t < 20)
            tmp += (D^(B&(C^D))) + 0x5A827999;
        else if ( t < 40)
            tmp += (B^C^D) + 0x6ED9EBA1;
        else if ( t < 60)
            tmp += ((B&C)|(D&(B|C))) + 0x8F1BBCDC;
        else
            tmp += (B^C^D) + 0xCA62C1D6;

        E = D;
        D = C;
        C = rol(30,B);
        B = A;
        A = tmp;
    }

    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
    ctx->state[4] += E;
}