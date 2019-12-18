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

__attribute__((used)) static int
is_legal_utf8(const unsigned char *bytes, int length)
{
    if (0 == bytes || 0 == length) return 0;

    unsigned char a;
    const unsigned char* srcptr = bytes + length;
    switch (length)
    {
    default:
        return 0;
        // Everything else falls through when true.
    case 4:
        if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return 0;
    case 3:
        if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return 0;
    case 2:
        a = (*--srcptr);
        switch (*bytes)
        {
        case 0xE0:
            if (a < 0xA0 || a > 0xBF) return 0;
            break;
        case 0xED:
            if (a < 0x80 || a > 0x9F) return 0;
            break;
        case 0xF0:
            if (a < 0x90 || a > 0xBF) return 0;
            break;
        case 0xF4:
            if (a < 0x80 || a > 0x8F) return 0;
            break;
        default:
            if (a < 0x80 || a > 0xBF) return 0;
        }
    case 1:
        if (*bytes >= 0x80 && *bytes < 0xC2) return 0;
    }
    return *bytes <= 0xF4;
}