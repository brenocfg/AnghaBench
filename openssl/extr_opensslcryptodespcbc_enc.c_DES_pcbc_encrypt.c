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
typedef  int DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DES_DECRYPT ; 
 int /*<<< orphan*/  DES_ENCRYPT ; 
 int /*<<< orphan*/  DES_encrypt1 (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2l (unsigned char const*,int) ; 
 int /*<<< orphan*/  c2ln (unsigned char const*,int,int,long) ; 
 int /*<<< orphan*/  l2c (int,unsigned char*) ; 
 int /*<<< orphan*/  l2cn (int,int,unsigned char*,long) ; 

void DES_pcbc_encrypt(const unsigned char *input, unsigned char *output,
                      long length, DES_key_schedule *schedule,
                      DES_cblock *ivec, int enc)
{
    register DES_LONG sin0, sin1, xor0, xor1, tout0, tout1;
    DES_LONG tin[2];
    const unsigned char *in;
    unsigned char *out, *iv;

    in = input;
    out = output;
    iv = &(*ivec)[0];

    if (enc) {
        c2l(iv, xor0);
        c2l(iv, xor1);
        for (; length > 0; length -= 8) {
            if (length >= 8) {
                c2l(in, sin0);
                c2l(in, sin1);
            } else
                c2ln(in, sin0, sin1, length);
            tin[0] = sin0 ^ xor0;
            tin[1] = sin1 ^ xor1;
            DES_encrypt1((DES_LONG *)tin, schedule, DES_ENCRYPT);
            tout0 = tin[0];
            tout1 = tin[1];
            xor0 = sin0 ^ tout0;
            xor1 = sin1 ^ tout1;
            l2c(tout0, out);
            l2c(tout1, out);
        }
    } else {
        c2l(iv, xor0);
        c2l(iv, xor1);
        for (; length > 0; length -= 8) {
            c2l(in, sin0);
            c2l(in, sin1);
            tin[0] = sin0;
            tin[1] = sin1;
            DES_encrypt1((DES_LONG *)tin, schedule, DES_DECRYPT);
            tout0 = tin[0] ^ xor0;
            tout1 = tin[1] ^ xor1;
            if (length >= 8) {
                l2c(tout0, out);
                l2c(tout1, out);
            } else
                l2cn(tout0, tout1, out, length);
            xor0 = tout0 ^ sin0;
            xor1 = tout1 ^ sin1;
        }
    }
    tin[0] = tin[1] = 0;
    sin0 = sin1 = xor0 = xor1 = tout0 = tout1 = 0;
}