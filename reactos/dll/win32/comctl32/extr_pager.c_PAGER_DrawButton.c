#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {scalar_t__ right; scalar_t__ left; scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DFCS_FLAT ; 
 int DFCS_INACTIVE ; 
 int DFCS_PUSHED ; 
 int DFCS_SCROLLDOWN ; 
 int DFCS_SCROLLLEFT ; 
 int DFCS_SCROLLRIGHT ; 
 int DFCS_SCROLLUP ; 
 int /*<<< orphan*/  DFC_SCROLL ; 
 int /*<<< orphan*/  DrawFrameControl (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
#define  PGF_DEPRESSED 131 
#define  PGF_GRAYED 130 
#define  PGF_HOT 129 
 int PGF_INVISIBLE ; 
#define  PGF_NORMAL 128 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void
PAGER_DrawButton(HDC hdc, COLORREF clrBk, RECT rc,
                 BOOL horz, BOOL topLeft, INT btnState)
{
    UINT flags;

    TRACE("rc = %s, btnState = %d\n", wine_dbgstr_rect(&rc), btnState);

    if (btnState == PGF_INVISIBLE)
        return;

    if ((rc.right - rc.left <= 0) || (rc.bottom - rc.top <= 0))
        return;

    if (horz)
        flags = topLeft ? DFCS_SCROLLLEFT : DFCS_SCROLLRIGHT;
    else
        flags = topLeft ? DFCS_SCROLLUP : DFCS_SCROLLDOWN;

    switch (btnState)
    {
    case PGF_HOT:
        break;
    case PGF_NORMAL:
        flags |= DFCS_FLAT;
        break;
    case PGF_DEPRESSED:
        flags |= DFCS_PUSHED;
        break;
    case PGF_GRAYED:
        flags |= DFCS_INACTIVE | DFCS_FLAT;
        break;
    }
    DrawFrameControl( hdc, &rc, DFC_SCROLL, flags );
}