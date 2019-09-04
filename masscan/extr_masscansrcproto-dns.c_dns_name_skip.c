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
 int dns_name_skip_validate (unsigned char const*,unsigned int,unsigned int,unsigned int) ; 

unsigned
dns_name_skip(const unsigned char px[], unsigned offset, unsigned max)
{
    unsigned name_length = 0;

    /* Loop through all labels
     * NOTE: the only way this loops around is in the case of a normal
     * label. All other conditions cause a 'return' from this function */
    for (;;) {
        if (name_length >= 255)
            return max + 1;

        if (offset >= max)
            return max + 1;

        switch (px[offset]>>6) {
        case 0:
            /* uncompressed label */
            if (px[offset] == 0) {
                return offset+1; /* end of domain name */
            } else {
                name_length += px[offset] + 1;
                offset += px[offset] + 1;
                continue;
            }
            break;
        case 3:
            /* 0xc0 = compressed name */
            return dns_name_skip_validate(px, offset, max, name_length);
        case 2:
            /* 0x40 - ENDS0 extended label type
             * rfc2671 section 3.1
             * I have no idea how to parse this */
            return max + 1; /* totally clueless how to parse it */
        case 1:
            return max + 1;
        }
    }
}