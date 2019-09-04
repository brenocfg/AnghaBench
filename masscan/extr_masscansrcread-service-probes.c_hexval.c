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
hexval(int c)
{
    switch (c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return c - '0';
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            return c - 'a' + 10;
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            return c - 'A' + 10;
        default:
            return (unsigned)~0;
    }
}