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

int _re1_5_namedclassmatch(const char *pc, const char *sp)
{
    // pc points to name of class
    int off = (*pc >> 5) & 1;
    if ((*pc | 0x20) == 'd') {
        if (!(*sp >= '0' && *sp <= '9')) {
            off ^= 1;
        }
    } else if ((*pc | 0x20) == 's') {
        if (!(*sp == ' ' || (*sp >= '\t' && *sp <= '\r'))) {
            off ^= 1;
        }
    } else { // w
        if (!((*sp >= 'A' && *sp <= 'Z') || (*sp >= 'a' && *sp <= 'z') || (*sp >= '0' && *sp <= '9') || *sp == '_')) {
            off ^= 1;
        }
    }
    return off;
}