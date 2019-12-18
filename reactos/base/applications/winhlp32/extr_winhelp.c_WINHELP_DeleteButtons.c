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
struct TYPE_5__ {TYPE_2__* first_button; } ;
typedef  TYPE_1__ WINHELP_WINDOW ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_2__ WINHELP_BUTTON ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void WINHELP_DeleteButtons(WINHELP_WINDOW* win)
{
    WINHELP_BUTTON*     b;
    WINHELP_BUTTON*     bp;

    for (b = win->first_button; b; b = bp)
    {
        DestroyWindow(b->hWnd);
        bp = b->next;
        HeapFree(GetProcessHeap(), 0, b);
    }
    win->first_button = NULL;
}