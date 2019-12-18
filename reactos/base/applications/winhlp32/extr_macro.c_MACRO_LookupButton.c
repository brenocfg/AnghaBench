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
struct TYPE_6__ {int /*<<< orphan*/  lpszID; struct TYPE_6__* next; } ;
typedef  TYPE_2__ WINHELP_BUTTON ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcmpiA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WINHELP_BUTTON**        MACRO_LookupButton(WINHELP_WINDOW* win, LPCSTR name)
{
    WINHELP_BUTTON**    b;

    for (b = &win->first_button; *b; b = &(*b)->next)
        if (!lstrcmpiA(name, (*b)->lpszID)) break;
    return b;
}