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
struct TYPE_3__ {int* state; int* cksm; } ;
typedef  int MD2_INT ;
typedef  TYPE_1__ MD2_CTX ;

/* Variables and functions */
 int MD2_BLOCK ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int*,int) ; 
 int* S ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void md2_block(MD2_CTX *c, const unsigned char *d)
{
    register MD2_INT t, *sp1, *sp2;
    register int i, j;
    MD2_INT state[48];

    sp1 = c->state;
    sp2 = c->cksm;
    j = sp2[MD2_BLOCK - 1];
    for (i = 0; i < 16; i++) {
        state[i] = sp1[i];
        state[i + 16] = t = d[i];
        state[i + 32] = (t ^ sp1[i]);
        j = sp2[i] ^= S[t ^ j];
    }
    t = 0;
    for (i = 0; i < 18; i++) {
        for (j = 0; j < 48; j += 8) {
            t = state[j + 0] ^= S[t];
            t = state[j + 1] ^= S[t];
            t = state[j + 2] ^= S[t];
            t = state[j + 3] ^= S[t];
            t = state[j + 4] ^= S[t];
            t = state[j + 5] ^= S[t];
            t = state[j + 6] ^= S[t];
            t = state[j + 7] ^= S[t];
        }
        t = (t + i) & 0xff;
    }
    memcpy(sp1, state, 16 * sizeof(MD2_INT));
    OPENSSL_cleanse(state, 48 * sizeof(MD2_INT));
}