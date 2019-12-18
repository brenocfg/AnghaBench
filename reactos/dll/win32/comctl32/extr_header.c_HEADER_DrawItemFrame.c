#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dwStyle; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_5__ {scalar_t__ bDown; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ HEADER_ITEM ;
typedef  TYPE_2__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BDR_RAISEDOUTER ; 
 int BF_ADJUST ; 
 int BF_BOTTOM ; 
 int BF_FLAT ; 
 int BF_RECT ; 
 int BF_RIGHT ; 
 int BF_SOFT ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDGE_ETCHED ; 
 int /*<<< orphan*/  EDGE_RAISED ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int HDS_BUTTONS ; 
 int HDS_FLAT ; 

__attribute__((used)) static void
HEADER_DrawItemFrame(HEADER_INFO *infoPtr, HDC hdc, RECT *r, const HEADER_ITEM *item)
{
    if (GetWindowTheme(infoPtr->hwndSelf)) return;

    if (!(infoPtr->dwStyle & HDS_FLAT))
    {
        if (infoPtr->dwStyle & HDS_BUTTONS) {
            if (item->bDown)
                DrawEdge (hdc, r, BDR_RAISEDOUTER, BF_RECT | BF_FLAT | BF_ADJUST);
            else
                DrawEdge (hdc, r, EDGE_RAISED, BF_RECT | BF_SOFT | BF_ADJUST);
        }
        else
            DrawEdge (hdc, r, EDGE_ETCHED, BF_BOTTOM | BF_RIGHT | BF_ADJUST);
    }
}