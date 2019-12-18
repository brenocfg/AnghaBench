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
typedef  int HPDF_INT32 ;

/* Variables and functions */
 int HPDF_INT_LEN ; 
 int HPDF_LIMIT_MAX_INT ; 
 int HPDF_LIMIT_MIN_INT ; 

char*
HPDF_IToA  (char        *s,
            HPDF_INT32   val,
            char        *eptr)
{
    char* t;
    char buf[HPDF_INT_LEN + 1];

    if (val < 0) {
        if (val < HPDF_LIMIT_MIN_INT)
            val = HPDF_LIMIT_MIN_INT;
        *s++ = '-';
        val = -val;
    } else if (val > HPDF_LIMIT_MAX_INT) {
        val = HPDF_LIMIT_MAX_INT;
    } else if (val == 0) {
        *s++ = '0';
    }

    t = buf + HPDF_INT_LEN;
    *t-- = 0;

    while (val > 0) {
        *t = (char)((char)(val % 10) + '0');
        val /= 10;
        t--;
    }

    t++;
    while (s < eptr && *t != 0)
      *s++ = *t++;
    *s = 0;

    return s;
}