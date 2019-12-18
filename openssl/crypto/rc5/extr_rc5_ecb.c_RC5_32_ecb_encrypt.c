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
typedef  int /*<<< orphan*/  RC5_32_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  RC5_32_decrypt (unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC5_32_encrypt (unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c2l (unsigned char const*,unsigned long) ; 
 int /*<<< orphan*/  l2c (unsigned long,unsigned char*) ; 

void RC5_32_ecb_encrypt(const unsigned char *in, unsigned char *out,
                        RC5_32_KEY *ks, int encrypt)
{
    unsigned long l, d[2];

    c2l(in, l);
    d[0] = l;
    c2l(in, l);
    d[1] = l;
    if (encrypt)
        RC5_32_encrypt(d, ks);
    else
        RC5_32_decrypt(d, ks);
    l = d[0];
    l2c(l, out);
    l = d[1];
    l2c(l, out);
    l = d[0] = d[1] = 0;
}