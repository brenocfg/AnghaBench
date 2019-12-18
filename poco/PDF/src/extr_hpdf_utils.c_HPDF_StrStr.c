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
typedef  scalar_t__ HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_MemCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ HPDF_StrLen (char const*,int) ; 

const char*
HPDF_StrStr  (const char   *s1,
              const char   *s2,
              HPDF_UINT     maxlen)
{
    HPDF_UINT len = HPDF_StrLen (s2, -1);

    if (!s1)
        return NULL;

    if (len == 0)
        return s1;

    if (maxlen == 0)
        maxlen = HPDF_StrLen (s1, -1);

    if (maxlen < len)
        return NULL;

    maxlen -= len;
    maxlen++;

    while (maxlen > 0) {
        if (HPDF_MemCmp ((HPDF_BYTE *)s1, (HPDF_BYTE *)s2, len) == 0)
            return s1;

        s1++;
        maxlen--;
    }

    return NULL;
}