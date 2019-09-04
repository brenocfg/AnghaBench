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
typedef  int int32_t ;

/* Variables and functions */

size_t utf8_check_full(const char *buffer, size_t size, int32_t *codepoint)
{
    size_t i;
    int32_t value = 0;
    unsigned char u = (unsigned char)buffer[0];

    if(size == 2)
    {
        value = u & 0x1F;
    }
    else if(size == 3)
    {
        value = u & 0xF;
    }
    else if(size == 4)
    {
        value = u & 0x7;
    }
    else
        return 0;

    for(i = 1; i < size; i++)
    {
        u = (unsigned char)buffer[i];

        if(u < 0x80 || u > 0xBF) {
            /* not a continuation byte */
            return 0;
        }

        value = (value << 6) + (u & 0x3F);
    }

    if(value > 0x10FFFF) {
        /* not in Unicode range */
        return 0;
    }

    else if(0xD800 <= value && value <= 0xDFFF) {
        /* invalid code point (UTF-16 surrogate halves) */
        return 0;
    }

    else if((size == 2 && value < 0x80) ||
            (size == 3 && value < 0x800) ||
            (size == 4 && value < 0x10000)) {
        /* overlong encoding */
        return 0;
    }

    if(codepoint)
        *codepoint = value;

    return 1;
}