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
 int /*<<< orphan*/  GET_DIGIT (int) ; 

__attribute__((used)) static int
jsonsl__get_uescape_16(const char *s)
{
    int ret = 0;
    int cur;

    #define GET_DIGIT(off) \
        cur = jsonsl__digit2int(s[off]); \
        if (cur == -1) { return -1; } \
        ret |= (cur << (12 - (off * 4)));

    GET_DIGIT(0);
    GET_DIGIT(1);
    GET_DIGIT(2);
    GET_DIGIT(3);
    #undef GET_DIGIT
    return ret;
}