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

int utf8_encode(int32_t codepoint, char *buffer, size_t *size)
{
    if(codepoint < 0)
        return -1;
    else if(codepoint < 0x80)
    {
        buffer[0] = (char)codepoint;
        *size = 1;
    }
    else if(codepoint < 0x800)
    {
        buffer[0] = 0xC0 + ((codepoint & 0x7C0) >> 6);
        buffer[1] = 0x80 + ((codepoint & 0x03F));
        *size = 2;
    }
    else if(codepoint < 0x10000)
    {
        buffer[0] = 0xE0 + ((codepoint & 0xF000) >> 12);
        buffer[1] = 0x80 + ((codepoint & 0x0FC0) >> 6);
        buffer[2] = 0x80 + ((codepoint & 0x003F));
        *size = 3;
    }
    else if(codepoint <= 0x10FFFF)
    {
        buffer[0] = 0xF0 + ((codepoint & 0x1C0000) >> 18);
        buffer[1] = 0x80 + ((codepoint & 0x03F000) >> 12);
        buffer[2] = 0x80 + ((codepoint & 0x000FC0) >> 6);
        buffer[3] = 0x80 + ((codepoint & 0x00003F));
        *size = 4;
    }
    else
        return -1;

    return 0;
}