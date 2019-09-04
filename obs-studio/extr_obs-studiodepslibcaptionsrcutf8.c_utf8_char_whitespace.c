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
typedef  char utf8_char_t ;

/* Variables and functions */

int utf8_char_whitespace(const utf8_char_t* c)
{
    // 0x7F is DEL
    if (!c || (c[0] >= 0 && c[0] <= ' ') || c[0] == 0x7F) {
        return 1;
    }

    // EIA608_CHAR_NO_BREAK_SPACE TODO other utf8 spaces
    if (0xC2 == (unsigned char)c[0] && 0xA0 == (unsigned char)c[1]) {
        return 1;
    }

    return 0;
}