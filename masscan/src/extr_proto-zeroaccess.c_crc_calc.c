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
 unsigned int* crc32_table ; 

__attribute__((used)) static unsigned
crc_calc(const unsigned char *px, unsigned length)
{
    unsigned i;
    unsigned crc;

    crc = (unsigned)~0;
    for (i = 0; i < length; i++) {
        crc = crc32_table[(crc ^ px[i]) & 0xff] ^ (crc >> 8);
    }
    crc = ~crc;

    return crc;
}