#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hMainWnd; TYPE_1__* page; } ;
typedef  TYPE_2__ WINHELP_WINDOW ;
struct TYPE_12__ {scalar_t__ x; scalar_t__ width; scalar_t__ y; scalar_t__ height; } ;
struct TYPE_11__ {scalar_t__ cpMin; scalar_t__ cpMax; scalar_t__ bHotSpot; struct TYPE_11__* next; } ;
struct TYPE_10__ {short x; short y; } ;
struct TYPE_8__ {TYPE_4__* first_link; } ;
typedef  TYPE_3__ POINTL ;
typedef  scalar_t__ LPARAM ;
typedef  TYPE_4__ HLPFILE_LINK ;
typedef  TYPE_5__ HLPFILE_HOTSPOTLINK ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_ID_TEXT ; 
 int /*<<< orphan*/  EM_CHARFROMPOS ; 
 int /*<<< orphan*/  EM_POSFROMCHAR ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HIWORD (scalar_t__) ; 
 scalar_t__ LOWORD (scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static HLPFILE_LINK* WINHELP_FindLink(WINHELP_WINDOW* win, LPARAM pos)
{
    HLPFILE_LINK*           link;
    POINTL                  mouse_ptl, char_ptl, char_next_ptl;
    DWORD                   cp;

    if (!win->page) return NULL;

    mouse_ptl.x = (short)LOWORD(pos);
    mouse_ptl.y = (short)HIWORD(pos);
    cp = SendMessageW(GetDlgItem(win->hMainWnd, CTL_ID_TEXT), EM_CHARFROMPOS,
                      0, (LPARAM)&mouse_ptl);

    for (link = win->page->first_link; link; link = link->next)
    {
        if (link->cpMin <= cp && cp <= link->cpMax)
        {
            /* check whether we're at end of line */
            SendMessageW(GetDlgItem(win->hMainWnd, CTL_ID_TEXT), EM_POSFROMCHAR,
                         (LPARAM)&char_ptl, cp);
            SendMessageW(GetDlgItem(win->hMainWnd, CTL_ID_TEXT), EM_POSFROMCHAR,
                         (LPARAM)&char_next_ptl, cp + 1);
            if (link->bHotSpot)
            {
                HLPFILE_HOTSPOTLINK*    hslink = (HLPFILE_HOTSPOTLINK*)link;
                if ((mouse_ptl.x < char_ptl.x + hslink->x) ||
                    (mouse_ptl.x >= char_ptl.x + hslink->x + hslink->width) ||
                    (mouse_ptl.y < char_ptl.y + hslink->y) ||
                    (mouse_ptl.y >= char_ptl.y + hslink->y + hslink->height))
                    continue;
                break;
            }
            if (char_next_ptl.y != char_ptl.y || mouse_ptl.x >= char_next_ptl.x)
                link = NULL;
            break;
        }
    }
    return link;
}