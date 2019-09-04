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
typedef  int u32 ;
struct TYPE_3__ {unsigned char const* c; } ;
typedef  TYPE_1__ chacha_buf ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  chacha20_core (TYPE_1__*,int*) ; 

void ChaCha20_ctr32(unsigned char *out, const unsigned char *inp,
                    size_t len, const unsigned int key[8],
                    const unsigned int counter[4])
{
    u32 input[16];
    chacha_buf buf;
    size_t todo, i;

    /* sigma constant "expand 32-byte k" in little-endian encoding */
    input[0] = ((u32)'e') | ((u32)'x'<<8) | ((u32)'p'<<16) | ((u32)'a'<<24);
    input[1] = ((u32)'n') | ((u32)'d'<<8) | ((u32)' '<<16) | ((u32)'3'<<24);
    input[2] = ((u32)'2') | ((u32)'-'<<8) | ((u32)'b'<<16) | ((u32)'y'<<24);
    input[3] = ((u32)'t') | ((u32)'e'<<8) | ((u32)' '<<16) | ((u32)'k'<<24);

    input[4] = key[0];
    input[5] = key[1];
    input[6] = key[2];
    input[7] = key[3];
    input[8] = key[4];
    input[9] = key[5];
    input[10] = key[6];
    input[11] = key[7];

    input[12] = counter[0];
    input[13] = counter[1];
    input[14] = counter[2];
    input[15] = counter[3];

    while (len > 0) {
        todo = sizeof(buf);
        if (len < todo)
            todo = len;

        chacha20_core(&buf, input);

        for (i = 0; i < todo; i++)
            out[i] = inp[i] ^ buf.c[i];
        out += todo;
        inp += todo;
        len -= todo;

        /*
         * Advance 32-bit counter. Note that as subroutine is so to
         * say nonce-agnostic, this limited counter width doesn't
         * prevent caller from implementing wider counter. It would
         * simply take two calls split on counter overflow...
         */
        input[12]++;
    }
}