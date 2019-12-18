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
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */

HPDF_BYTE*
HPDF_StrCpy  (char          *out,
              const char    *in,
              char          *eptr)
{
    if (in != NULL) {
        while (eptr > out && *in != 0)
            *out++ = *in++;
    }

    *out = 0;

    return (HPDF_BYTE *)out;
}