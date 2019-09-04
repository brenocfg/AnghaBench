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
typedef  int utf8_char_t ;

/* Variables and functions */

size_t utf8_char_length(const utf8_char_t* c)
{
    // count null term as zero size
    if (!c || 0x00 == c[0]) {
        return 0;
    }

    static const size_t _utf8_char_length[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 3, 4, 0
    };

    return _utf8_char_length[(c[0] >> 3) & 0x1F];
}