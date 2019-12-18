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
typedef  int HPDF_INT ;
typedef  int HPDF_DOUBLE ;
typedef  scalar_t__ HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ HPDF_FALSE ; 
 scalar_t__ HPDF_IS_WHITE_SPACE (char const) ; 
 scalar_t__ HPDF_TRUE ; 

HPDF_DOUBLE
HPDF_AToF  (const char  *s)
{
    HPDF_BOOL flg = HPDF_FALSE;
    HPDF_INT i = 0;
    HPDF_DOUBLE v;
    HPDF_INT tmp = 1;

    /* increment pointer until the charactor of 's' is not
     * white-space-charactor.
     */
    while (*s) {
        if (HPDF_IS_WHITE_SPACE(*s))
            s++;
        else {
            if (*s == '-') {
                flg = HPDF_TRUE;
                s++;
            }
            break;
        }
    }

    while (*s >= '0' && *s <= '9') {
        if (i > 3276)
            break;

        i *= 10;
        i += *s - '0';
        s++;
    }

    if (*s == '.') {
        s++;
        while (*s >= '0' && *s <= '9') {
            if (i > 214748364)
                break;

            i *= 10;
            i += *s - '0';
            s++;
            tmp *= 10;
        }
    }

    v = (HPDF_DOUBLE)i / tmp;

    if (flg)
        v *= -1;

    return v;
}