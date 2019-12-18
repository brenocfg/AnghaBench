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
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  scalar_t__ HPDF_INT ;

/* Variables and functions */

HPDF_UINT
HPDF_StrLen  (const char   *s,
              HPDF_INT      maxlen)
{
    HPDF_INT len = 0;

    if (!s)
        return 0;

    while (*s != 0 && (maxlen < 0 || len < maxlen)) {
        s++;
        len++;
    }

    return (HPDF_UINT)len;
}