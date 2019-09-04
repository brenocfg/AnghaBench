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

__attribute__((used)) static unsigned
zadecrypt(const unsigned char *src, size_t src_len, unsigned char *dst, size_t dst_len)
{
    unsigned key;
    size_t i;

    key = 'f'<<24 | 't'<<16 | 'p'<<8 | '2'<<0;

    for (i=0; i<dst_len && i<src_len; i+=4) {
        dst[i+0] = src[i+0] ^ (unsigned char)(key>> 0);
        dst[i+1] = src[i+1] ^ (unsigned char)(key>> 8);
        dst[i+2] = src[i+2] ^ (unsigned char)(key>>16);
        dst[i+3] = src[i+3] ^ (unsigned char)(key>>24);

        key = key<<1 | key>>31;
    }

    return (unsigned)src_len;
}