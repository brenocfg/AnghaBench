#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  lfUnderline; } ;
struct TYPE_10__ {int /*<<< orphan*/  Self; int /*<<< orphan*/  BreakChar; int /*<<< orphan*/ * LinkFont; int /*<<< orphan*/  Font; } ;
struct TYPE_9__ {int /*<<< orphan*/  tmBreakChar; } ;
typedef  TYPE_1__ TEXTMETRICW ;
typedef  TYPE_2__ SYSLINK_INFO ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_3__ LOGFONTW ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateFontIndirectW (TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetObjectW (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 scalar_t__ GetTextMetricsW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int RDW_INVALIDATE ; 
 int RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSLINK_Render (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static HFONT SYSLINK_SetFont (SYSLINK_INFO *infoPtr, HFONT hFont, BOOL bRedraw)
{
    HDC hdc;
    LOGFONTW lf;
    TEXTMETRICW tm;
    RECT rcClient;
    HFONT hOldFont = infoPtr->Font;
    infoPtr->Font = hFont;
    
    /* free the underline font */
    if(infoPtr->LinkFont != NULL)
    {
        DeleteObject(infoPtr->LinkFont);
        infoPtr->LinkFont = NULL;
    }

    /* Render text position and word wrapping in memory */
    if (GetClientRect(infoPtr->Self, &rcClient))
    {
        hdc = GetDC(infoPtr->Self);
        if(hdc != NULL)
        {
            /* create a new underline font */
            if(GetTextMetricsW(hdc, &tm) &&
               GetObjectW(infoPtr->Font, sizeof(LOGFONTW), &lf))
            {
                lf.lfUnderline = TRUE;
                infoPtr->LinkFont = CreateFontIndirectW(&lf);
                infoPtr->BreakChar = tm.tmBreakChar;
            }
            else
            {
                ERR("Failed to create link font!\n");
            }

            SYSLINK_Render(infoPtr, hdc, &rcClient);
            ReleaseDC(infoPtr->Self, hdc);
        }
    }
    
    if(bRedraw)
    {
        RedrawWindow(infoPtr->Self, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    }
    
    return hOldFont;
}