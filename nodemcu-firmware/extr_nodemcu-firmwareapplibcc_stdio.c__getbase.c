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

__attribute__((used)) static char *
_getbase(char *p, int *basep)
{
    if (p[0] == '0') {
        switch (p[1]) {
        case 'x':
            *basep = 16;
            break;
        case 't': case 'n':
            *basep = 10;
            break;
        case 'o':
            *basep = 8;
            break;
        default:
            *basep = 10;
            return (p);
        }
        return (p + 2);
    }
    *basep = 10;
    return (p);
}