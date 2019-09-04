#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  first_macro; struct TYPE_4__* next; } ;
typedef  TYPE_1__ HLPFILE_PAGE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_DeleteMacro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void HLPFILE_DeletePage(HLPFILE_PAGE* page)
{
    HLPFILE_PAGE* next;

    while (page)
    {
        next = page->next;
        HLPFILE_DeleteMacro(page->first_macro);
        HeapFree(GetProcessHeap(), 0, page);
        page = next;
    }
}