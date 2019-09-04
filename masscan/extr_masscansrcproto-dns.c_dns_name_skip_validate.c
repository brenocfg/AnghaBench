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
dns_name_skip_validate(const unsigned char *px, unsigned offset, unsigned length, unsigned name_length)
{
    unsigned ERROR = length + 1;
    unsigned result = offset + 2;
    unsigned recursion = 0;

    /* 'for all labels' */
    for (;;) {
        unsigned len;

        /* validate: the eventual uncompressed name will be less than 255 */
        if (name_length >= 255)
            return ERROR;

        /* validate: haven't gone off end of packet */
        if (offset >= length)
            return ERROR;

        /* grab length of next label */
        len = px[offset];

        /* Do two types of processing, either a compression code or a
         * original label. Note that we can alternate back and forth
         * between these two states. */
        if (len & 0xC0) {
            /* validate: top 2 bits are 11*/
            if ((len & 0xC0) != 0xC0)
                return ERROR;

            /* validate: enough bytes left for 2 byte compression field */
            if (offset + 1 >= length)
                return ERROR;

            /* follow the compression pointer to the next location */
            offset = (px[offset]&0x3F)<<8 | px[offset+1];

            /* validate: follow a max of 4 links */
            if (++recursion > 4)
                return ERROR;
        } else {
            /* we have a normal label */
            recursion = 0;

            /* If the label-length is zero, then that meaans we've reached
             * the end of the name */
            if (len == 0) {
                return result; /* end of domain name */
            }

            /* There are more labels to come, therefore skip this and go
             * to the next one */
            name_length += len + 1;
            offset += len + 1;
        }
    }
}