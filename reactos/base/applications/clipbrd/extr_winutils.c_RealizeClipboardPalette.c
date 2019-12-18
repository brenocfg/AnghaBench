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
typedef  int /*<<< orphan*/  HPALETTE ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_PALETTE ; 
 int FALSE ; 
 scalar_t__ GDI_ERROR ; 
 int /*<<< orphan*/  GetClipboardData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsClipboardFormatAvailable (int /*<<< orphan*/ ) ; 
 scalar_t__ RealizePalette (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectPalette (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

BOOL RealizeClipboardPalette(HDC hdc)
{
    BOOL Success;
    HPALETTE hPalette, hOldPalette;

    if (!IsClipboardFormatAvailable(CF_PALETTE))
        return FALSE;

    hPalette = GetClipboardData(CF_PALETTE);
    if (!hPalette)
        return FALSE;

    hOldPalette = SelectPalette(hdc, hPalette, FALSE);
    if (!hOldPalette)
        return FALSE;

    Success = (RealizePalette(hdc) != GDI_ERROR);

    SelectPalette(hdc, hOldPalette, FALSE);

    return Success;
}