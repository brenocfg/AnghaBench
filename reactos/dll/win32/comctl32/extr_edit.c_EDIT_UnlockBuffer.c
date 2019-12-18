#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lock_count; int /*<<< orphan*/ * text; scalar_t__ hloc32W; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalUnlock (scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_UnlockBuffer(EDITSTATE *es, BOOL force)
{
    /* Edit window might be already destroyed */
    if (!IsWindow(es->hwndSelf))
    {
        WARN("edit hwnd %p already destroyed\n", es->hwndSelf);
        return;
    }

    if (!es->lock_count)
    {
        ERR("lock_count == 0 ... please report\n");
        return;
    }

    if (!es->text)
    {
        ERR("es->text == 0 ... please report\n");
        return;
    }

    if (force || (es->lock_count == 1))
    {
        if (es->hloc32W)
        {
            LocalUnlock(es->hloc32W);
            es->text = NULL;
        }
        else
        {
            ERR("no buffer ... please report\n");
            return;
        }

    }

    es->lock_count--;
}