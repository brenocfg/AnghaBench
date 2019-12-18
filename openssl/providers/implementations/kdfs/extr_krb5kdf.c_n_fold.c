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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void n_fold(unsigned char *block, unsigned int blocksize,
                   const unsigned char *constant, size_t constant_len)
{
    unsigned int tmp, gcd, remainder, lcm, carry;
    int b, l;

    if (constant_len == blocksize) {
        memcpy(block, constant, constant_len);
        return;
    }

    /* Least Common Multiple of lengths: LCM(a,b)*/
    gcd = blocksize;
    remainder = constant_len;
    /* Calculate Great Common Divisor first GCD(a,b) */
    while (remainder != 0) {
        tmp = gcd % remainder;
        gcd = remainder;
        remainder = tmp;
    }
    /* resulting a is the GCD, LCM(a,b) = |a*b|/GCD(a,b) */
    lcm = blocksize * constant_len / gcd;

    /* now spread out the bits */
    memset(block, 0, blocksize);

    /* last to first to be able to bring carry forward */
    carry = 0;
    for (l = lcm - 1; l >= 0; l--) {
        unsigned int rotbits, rshift, rbyte;

        /* destination byte in block is l % N */
        b = l % blocksize;
        /* Our virtual s buffer is R = L/K long (K = constant_len) */
        /* So we rotate backwards from R-1 to 0 (none) rotations */
        rotbits = 13 * (l / constant_len);
        /* find the byte on s where rotbits falls onto */
        rbyte = l - (rotbits / 8);
        /* calculate how much shift on that byte */
        rshift = rotbits & 0x07;
        /* rbyte % constant_len gives us the unrotated byte in the
         * constant buffer, get also the previous byte then
         * appropriately shift them to get the rotated byte we need */
        tmp = (constant[(rbyte-1) % constant_len] << (8 - rshift)
               | constant[rbyte % constant_len] >> rshift)
              & 0xff;
        /* add with carry to any value placed by previous passes */
        tmp += carry + block[b];
        block[b] = tmp & 0xff;
        /* save any carry that may be left */
        carry = tmp >> 8;
    }

    /* if any carry is left at the end, add it through the number */
    for (b = blocksize - 1; b >= 0 && carry != 0; b--) {
        carry += block[b];
        block[b] = carry & 0xff;
        carry >>= 8;
    }
}