#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dib ;
struct TYPE_6__ {int biHeight; int biWidth; } ;
struct TYPE_5__ {int bmBitsPixel; int* bmBits; } ;
struct TYPE_7__ {TYPE_2__ dsBmih; TYPE_1__ dsBm; } ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  TYPE_3__ DIBSECTION ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GetObjectW (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL prepare_alpha (HBITMAP bmp, BOOL* hasAlpha)
{
    DIBSECTION dib;
    int n;
    BYTE* p;

    *hasAlpha = FALSE;

    if (!bmp || GetObjectW( bmp, sizeof(dib), &dib ) != sizeof(dib))
        return FALSE;

    if(dib.dsBm.bmBitsPixel != 32)
        /* nothing to do */
        return TRUE;

    p = dib.dsBm.bmBits;
    n = dib.dsBmih.biHeight * dib.dsBmih.biWidth;
    /* AlphaBlend() wants premultiplied alpha, so do that now */
    while (n-- > 0)
    {
        int a = p[3]+1;
        p[0] = (p[0] * a) >> 8;
        p[1] = (p[1] * a) >> 8;
        p[2] = (p[2] * a) >> 8;
        p += 4;

        if (a != 256)
            *hasAlpha = TRUE;
    }

    return TRUE;
}