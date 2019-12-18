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
typedef  scalar_t__ HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ HPDF_FALSE ; 
 scalar_t__ HPDF_IS_WHITE_SPACE (char const) ; 
 scalar_t__ HPDF_TRUE ; 

HPDF_INT
HPDF_AToI  (const char  *s)
{
    HPDF_BOOL flg = HPDF_FALSE;
    HPDF_INT  v = 0;

    if (!s) {
        return 0;
    }

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
        v *= 10;
        v += *s - '0';
        s++;
    }

    if (flg)
        v *= -1;

    return v;
}