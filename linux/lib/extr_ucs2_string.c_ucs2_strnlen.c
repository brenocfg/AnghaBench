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
typedef  int /*<<< orphan*/  ucs2_char_t ;

/* Variables and functions */

unsigned long
ucs2_strnlen(const ucs2_char_t *s, size_t maxlength)
{
        unsigned long length = 0;

        while (*s++ != 0 && length < maxlength)
                length++;
        return length;
}