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
dtype_kind_to_ordering(char kind)
{
    switch (kind) {
        /* Boolean kind */
        case 'b':
            return 0;
        /* Unsigned int kind */
        case 'u':
            return 1;
        /* Signed int kind */
        case 'i':
            return 2;
        /* Float kind */
        case 'f':
            return 4;
        /* Complex kind */
        case 'c':
            return 5;
        /* String kind */
        case 'S':
        case 'a':
            return 6;
        /* Unicode kind */
        case 'U':
            return 7;
        /* Void kind */
        case 'V':
            return 8;
        /* Object kind */
        case 'O':
            return 9;
        /*
         * Anything else, like datetime, is special cased to
         * not fit in this hierarchy
         */
        default:
            return -1;
    }
}