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
struct TYPE_5__ {int /*<<< orphan*/ * string; struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__* LPHIST_ENTRY ;
typedef  int /*<<< orphan*/ * LPCTSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__* Bottom ; 
 TYPE_1__* Top ; 
 TYPE_1__* curr_ptr ; 

LPCTSTR PeekHistory(INT dir)
{
    LPHIST_ENTRY entry = curr_ptr;

    ASSERT(Top && Bottom);

    if (dir == 0)
        return NULL;

    if (dir < 0)
    {
        /* key up */
        if (entry->next == Top || entry == Top)
        {
#ifdef WRAP_HISTORY
            entry = Bottom;
#else
            return NULL;
#endif
        }
        entry = entry->next;
    }
    else
    {
        /* key down */
        if (entry->prev == Bottom || entry == Bottom)
        {
#ifdef WRAP_HISTORY
            entry = Top;
#else
            return NULL;
#endif
        }
        entry = entry->prev;
    }

    return entry->string;
}