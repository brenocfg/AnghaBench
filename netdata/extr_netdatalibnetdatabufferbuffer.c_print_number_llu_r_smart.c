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

inline char *print_number_llu_r_smart(char *str, unsigned long long uvalue) {
#ifdef ENVIRONMENT32
    if(uvalue > (unsigned long long)0xffffffff)
        str = print_number_llu_r(str, uvalue);
    else
        str = print_number_lu_r(str, uvalue);
#else
    do *str++ = (char)('0' + (uvalue % 10)); while(uvalue /= 10);
#endif

    return str;
}