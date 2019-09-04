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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static char *
jsonsl__writeutf8(uint32_t pt, char *out)
{
    #define ADD_OUTPUT(c) *out = (char)(c); out++;

    if (pt < 0x80) {
        ADD_OUTPUT(pt);
    } else if (pt < 0x800) {
        ADD_OUTPUT((pt >> 6) | 0xC0);
        ADD_OUTPUT((pt & 0x3F) | 0x80);
    } else if (pt < 0x10000) {
        ADD_OUTPUT((pt >> 12) | 0xE0);
        ADD_OUTPUT(((pt >> 6) & 0x3F) | 0x80);
        ADD_OUTPUT((pt & 0x3F) | 0x80);
    } else {
        ADD_OUTPUT((pt >> 18) | 0xF0);
        ADD_OUTPUT(((pt >> 12) & 0x3F) | 0x80);
        ADD_OUTPUT(((pt >> 6) & 0x3F) | 0x80);
        ADD_OUTPUT((pt & 0x3F) | 0x80);
    }
    return out;
    #undef ADD_OUTPUT
}