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

int UTF8_putc(unsigned char *str, int len, unsigned long value)
{
    if (!str)
        len = 6;                /* Maximum we will need */
    else if (len <= 0)
        return -1;
    if (value < 0x80) {
        if (str)
            *str = (unsigned char)value;
        return 1;
    }
    if (value < 0x800) {
        if (len < 2)
            return -1;
        if (str) {
            *str++ = (unsigned char)(((value >> 6) & 0x1f) | 0xc0);
            *str = (unsigned char)((value & 0x3f) | 0x80);
        }
        return 2;
    }
    if (value < 0x10000) {
        if (len < 3)
            return -1;
        if (str) {
            *str++ = (unsigned char)(((value >> 12) & 0xf) | 0xe0);
            *str++ = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
            *str = (unsigned char)((value & 0x3f) | 0x80);
        }
        return 3;
    }
    if (value < 0x200000) {
        if (len < 4)
            return -1;
        if (str) {
            *str++ = (unsigned char)(((value >> 18) & 0x7) | 0xf0);
            *str++ = (unsigned char)(((value >> 12) & 0x3f) | 0x80);
            *str++ = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
            *str = (unsigned char)((value & 0x3f) | 0x80);
        }
        return 4;
    }
    if (value < 0x4000000) {
        if (len < 5)
            return -1;
        if (str) {
            *str++ = (unsigned char)(((value >> 24) & 0x3) | 0xf8);
            *str++ = (unsigned char)(((value >> 18) & 0x3f) | 0x80);
            *str++ = (unsigned char)(((value >> 12) & 0x3f) | 0x80);
            *str++ = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
            *str = (unsigned char)((value & 0x3f) | 0x80);
        }
        return 5;
    }
    if (len < 6)
        return -1;
    if (str) {
        *str++ = (unsigned char)(((value >> 30) & 0x1) | 0xfc);
        *str++ = (unsigned char)(((value >> 24) & 0x3f) | 0x80);
        *str++ = (unsigned char)(((value >> 18) & 0x3f) | 0x80);
        *str++ = (unsigned char)(((value >> 12) & 0x3f) | 0x80);
        *str++ = (unsigned char)(((value >> 6) & 0x3f) | 0x80);
        *str = (unsigned char)((value & 0x3f) | 0x80);
    }
    return 6;
}