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
typedef  int HPDF_UINT32 ;
typedef  int HPDF_UINT ;

/* Variables and functions */
 int HPDF_LIMIT_MAX_INT ; 

char*
HPDF_IToA2  (char         *s,
             HPDF_UINT32   val,
             HPDF_UINT     len)
{
    char* t;
    char* u;

    if (val > HPDF_LIMIT_MAX_INT)
        val = HPDF_LIMIT_MAX_INT;

    u = s + len - 1;
    *u = 0;
    t = u - 1;
    while (val > 0 && t >= s) {
        *t = (char)((char)(val % 10) + '0');
        val /= 10;
        t--;
    }

    while (s <= t)
        *t-- = '0';

    return s + len - 1;
}