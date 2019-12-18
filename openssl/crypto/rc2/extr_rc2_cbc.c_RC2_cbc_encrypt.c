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
typedef  int /*<<< orphan*/  RC2_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  RC2_decrypt (unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC2_encrypt (unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c2l (unsigned char const*,unsigned long) ; 
 int /*<<< orphan*/  c2ln (unsigned char const*,unsigned long,unsigned long,long) ; 
 int /*<<< orphan*/  l2c (unsigned long,unsigned char*) ; 
 int /*<<< orphan*/  l2cn (unsigned long,unsigned long,unsigned char*,long) ; 

void RC2_cbc_encrypt(const unsigned char *in, unsigned char *out, long length,
                     RC2_KEY *ks, unsigned char *iv, int encrypt)
{
    register unsigned long tin0, tin1;
    register unsigned long tout0, tout1, xor0, xor1;
    register long l = length;
    unsigned long tin[2];

    if (encrypt) {
        c2l(iv, tout0);
        c2l(iv, tout1);
        iv -= 8;
        for (l -= 8; l >= 0; l -= 8) {
            c2l(in, tin0);
            c2l(in, tin1);
            tin0 ^= tout0;
            tin1 ^= tout1;
            tin[0] = tin0;
            tin[1] = tin1;
            RC2_encrypt(tin, ks);
            tout0 = tin[0];
            l2c(tout0, out);
            tout1 = tin[1];
            l2c(tout1, out);
        }
        if (l != -8) {
            c2ln(in, tin0, tin1, l + 8);
            tin0 ^= tout0;
            tin1 ^= tout1;
            tin[0] = tin0;
            tin[1] = tin1;
            RC2_encrypt(tin, ks);
            tout0 = tin[0];
            l2c(tout0, out);
            tout1 = tin[1];
            l2c(tout1, out);
        }
        l2c(tout0, iv);
        l2c(tout1, iv);
    } else {
        c2l(iv, xor0);
        c2l(iv, xor1);
        iv -= 8;
        for (l -= 8; l >= 0; l -= 8) {
            c2l(in, tin0);
            tin[0] = tin0;
            c2l(in, tin1);
            tin[1] = tin1;
            RC2_decrypt(tin, ks);
            tout0 = tin[0] ^ xor0;
            tout1 = tin[1] ^ xor1;
            l2c(tout0, out);
            l2c(tout1, out);
            xor0 = tin0;
            xor1 = tin1;
        }
        if (l != -8) {
            c2l(in, tin0);
            tin[0] = tin0;
            c2l(in, tin1);
            tin[1] = tin1;
            RC2_decrypt(tin, ks);
            tout0 = tin[0] ^ xor0;
            tout1 = tin[1] ^ xor1;
            l2cn(tout0, tout1, out, l + 8);
            xor0 = tin0;
            xor1 = tin1;
        }
        l2c(xor0, iv);
        l2c(xor1, iv);
    }
    tin0 = tin1 = tout0 = tout1 = xor0 = xor1 = 0;
    tin[0] = tin[1] = 0;
}