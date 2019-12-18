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
 char const Class ; 

int _re1_5_classmatch(const char *pc, const char *sp)
{
    // pc points to "cnt" byte after opcode
    int is_positive = (pc[-1] == Class);
    int cnt = *pc++;
    while (cnt--) {
        if (*sp >= *pc && *sp <= pc[1]) return is_positive;
        pc += 2;
    }
    return !is_positive;
}