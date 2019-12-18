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
typedef  size_t uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
asn1_length(const unsigned char *px, uint64_t length, uint64_t *r_offset)
{
    uint64_t result;

    /* check for errors */
    if ( (*r_offset >= length)
        || ((px[*r_offset] & 0x80)
        && ((*r_offset) + (px[*r_offset]&0x7F) >= length))) {
        *r_offset = length;
        return 0xFFFFffff;
    }

    /* grab the byte's value */
    result = px[(*r_offset)++];


    if (result & 0x80) {
        unsigned length_of_length = result & 0x7F;
        if (length_of_length == 0) {
            *r_offset = length;
            return 0xFFFFffff;
        }
        result = 0;
        while (length_of_length) {
            result = result * 256 + px[(*r_offset)++];
            if (result > 0x10000) {
                *r_offset = length;
                return 0xFFFFffff;
            }
            length_of_length--;
        }
    }
    return result;
}