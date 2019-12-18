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
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  unsigned char* DES_cblock ;
typedef  int /*<<< orphan*/  DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DES_encrypt3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c2l (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2ln (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  l2c (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  l2cn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 

void DES_ede3_cfb_encrypt(const unsigned char *in, unsigned char *out,
                          int numbits, long length, DES_key_schedule *ks1,
                          DES_key_schedule *ks2, DES_key_schedule *ks3,
                          DES_cblock *ivec, int enc)
{
    register DES_LONG d0, d1, v0, v1;
    register unsigned long l = length, n = ((unsigned int)numbits + 7) / 8;
    register int num = numbits, i;
    DES_LONG ti[2];
    unsigned char *iv;
    unsigned char ovec[16];

    if (num > 64)
        return;
    iv = &(*ivec)[0];
    c2l(iv, v0);
    c2l(iv, v1);
    if (enc) {
        while (l >= n) {
            l -= n;
            ti[0] = v0;
            ti[1] = v1;
            DES_encrypt3(ti, ks1, ks2, ks3);
            c2ln(in, d0, d1, n);
            in += n;
            d0 ^= ti[0];
            d1 ^= ti[1];
            l2cn(d0, d1, out, n);
            out += n;
            /*
             * 30-08-94 - eay - changed because l>>32 and l<<32 are bad under
             * gcc :-(
             */
            if (num == 32) {
                v0 = v1;
                v1 = d0;
            } else if (num == 64) {
                v0 = d0;
                v1 = d1;
            } else {
                iv = &ovec[0];
                l2c(v0, iv);
                l2c(v1, iv);
                l2c(d0, iv);
                l2c(d1, iv);
                /* shift ovec left most of the bits... */
                memmove(ovec, ovec + num / 8, 8 + (num % 8 ? 1 : 0));
                /* now the remaining bits */
                if (num % 8 != 0)
                    for (i = 0; i < 8; ++i) {
                        ovec[i] <<= num % 8;
                        ovec[i] |= ovec[i + 1] >> (8 - num % 8);
                    }
                iv = &ovec[0];
                c2l(iv, v0);
                c2l(iv, v1);
            }
        }
    } else {
        while (l >= n) {
            l -= n;
            ti[0] = v0;
            ti[1] = v1;
            DES_encrypt3(ti, ks1, ks2, ks3);
            c2ln(in, d0, d1, n);
            in += n;
            /*
             * 30-08-94 - eay - changed because l>>32 and l<<32 are bad under
             * gcc :-(
             */
            if (num == 32) {
                v0 = v1;
                v1 = d0;
            } else if (num == 64) {
                v0 = d0;
                v1 = d1;
            } else {
                iv = &ovec[0];
                l2c(v0, iv);
                l2c(v1, iv);
                l2c(d0, iv);
                l2c(d1, iv);
                /* shift ovec left most of the bits... */
                memmove(ovec, ovec + num / 8, 8 + (num % 8 ? 1 : 0));
                /* now the remaining bits */
                if (num % 8 != 0)
                    for (i = 0; i < 8; ++i) {
                        ovec[i] <<= num % 8;
                        ovec[i] |= ovec[i + 1] >> (8 - num % 8);
                    }
                iv = &ovec[0];
                c2l(iv, v0);
                c2l(iv, v1);
            }
            d0 ^= ti[0];
            d1 ^= ti[1];
            l2cn(d0, d1, out, n);
            out += n;
        }
    }
    iv = &(*ivec)[0];
    l2c(v0, iv);
    l2c(v1, iv);
    v0 = v1 = d0 = d1 = ti[0] = ti[1] = 0;
}