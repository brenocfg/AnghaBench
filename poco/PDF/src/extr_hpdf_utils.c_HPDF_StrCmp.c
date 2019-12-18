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
typedef  int HPDF_BYTE ;

/* Variables and functions */

HPDF_INT
HPDF_StrCmp  (const char   *s1,
              const char   *s2)
{
    if (!s1 || !s2) {
        if (!s1 && s2)
            return -1;
        else
            return 1;
    }

    while (*s1 == *s2) {
        s1++;
        s2++;
        if (*s1 == 0 || *s2 == 0)
            break;
    }

    return (HPDF_BYTE)*s1 - (HPDF_BYTE)*s2;
}