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
typedef  int uint32_t ;
typedef  int uint32 ;

/* Variables and functions */
 scalar_t__ isdigit (char) ; 

uint32_t lwip_getul(char *str)
{
    uint32 ret = 0;

    while (isdigit(*str))
    {
        ret = ret * 10 + *str++ - '0';
    }

    return ret;
}