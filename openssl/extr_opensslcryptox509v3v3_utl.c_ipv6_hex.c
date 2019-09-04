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
 int OPENSSL_hexchar2int (unsigned char) ; 

__attribute__((used)) static int ipv6_hex(unsigned char *out, const char *in, int inlen)
{
    unsigned char c;
    unsigned int num = 0;
    int x;

    if (inlen > 4)
        return 0;
    while (inlen--) {
        c = *in++;
        num <<= 4;
        x = OPENSSL_hexchar2int(c);
        if (x < 0)
            return 0;
        num |= (char)x;
    }
    out[0] = num >> 8;
    out[1] = num & 0xff;
    return 1;
}