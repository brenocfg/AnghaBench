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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  (* ctr128_f ) (unsigned char*,unsigned char*,int,void const*,unsigned char*) ;

/* Variables and functions */
 unsigned int GETU32 (unsigned char*) ; 
 int /*<<< orphan*/  PUTU32 (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  ctr96_inc (unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,int,void const*,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,unsigned char*,int,void const*,unsigned char*) ; 

void CRYPTO_ctr128_encrypt_ctr32(const unsigned char *in, unsigned char *out,
                                 size_t len, const void *key,
                                 unsigned char ivec[16],
                                 unsigned char ecount_buf[16],
                                 unsigned int *num, ctr128_f func)
{
    unsigned int n, ctr32;

    n = *num;

    while (n && len) {
        *(out++) = *(in++) ^ ecount_buf[n];
        --len;
        n = (n + 1) % 16;
    }

    ctr32 = GETU32(ivec + 12);
    while (len >= 16) {
        size_t blocks = len / 16;
        /*
         * 1<<28 is just a not-so-small yet not-so-large number...
         * Below condition is practically never met, but it has to
         * be checked for code correctness.
         */
        if (sizeof(size_t) > sizeof(unsigned int) && blocks > (1U << 28))
            blocks = (1U << 28);
        /*
         * As (*func) operates on 32-bit counter, caller
         * has to handle overflow. 'if' below detects the
         * overflow, which is then handled by limiting the
         * amount of blocks to the exact overflow point...
         */
        ctr32 += (u32)blocks;
        if (ctr32 < blocks) {
            blocks -= ctr32;
            ctr32 = 0;
        }
        (*func) (in, out, blocks, key, ivec);
        /* (*ctr) does not update ivec, caller does: */
        PUTU32(ivec + 12, ctr32);
        /* ... overflow was detected, propagate carry. */
        if (ctr32 == 0)
            ctr96_inc(ivec);
        blocks *= 16;
        len -= blocks;
        out += blocks;
        in += blocks;
    }
    if (len) {
        memset(ecount_buf, 0, 16);
        (*func) (ecount_buf, ecount_buf, 1, key, ivec);
        ++ctr32;
        PUTU32(ivec + 12, ctr32);
        if (ctr32 == 0)
            ctr96_inc(ivec);
        while (len--) {
            out[n] = in[n] ^ ecount_buf[n];
            ++n;
        }
    }

    *num = n;
}