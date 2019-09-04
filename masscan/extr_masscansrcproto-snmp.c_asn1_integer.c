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
typedef  int uint64_t ;

/* Variables and functions */
 int asn1_length (unsigned char const*,int,int*) ; 

__attribute__((used)) static uint64_t
asn1_integer(const unsigned char *px, uint64_t length, uint64_t *r_offset)
{
    uint64_t int_length;
    uint64_t result;

    if (px[(*r_offset)++] != 0x02) {
        *r_offset = length;
        return 0xFFFFffff;
    }

    int_length = asn1_length(px, length, r_offset);
    if (int_length == 0xFFFFffff) {
        *r_offset = length;
        return 0xFFFFffff;
    }
    if (*r_offset + int_length > length) {
        *r_offset = length;
        return 0xFFFFffff;
    }
    if (int_length > 20) {
        *r_offset = length;
        return 0xFFFFffff;
    }

    result = 0;
    while (int_length--)
        result = result * 256 + px[(*r_offset)++];

    return result;
}