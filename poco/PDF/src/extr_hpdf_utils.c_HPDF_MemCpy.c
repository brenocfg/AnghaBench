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

HPDF_BYTE*
HPDF_MemCpy  (HPDF_BYTE*         out,
              const HPDF_BYTE   *in,
              HPDF_UINT          n)
{
    while (n > 0) {
        *out++ = *in++;
        n--;
    }

    return out;
}