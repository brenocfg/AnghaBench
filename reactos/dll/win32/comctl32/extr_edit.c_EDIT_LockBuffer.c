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
struct TYPE_3__ {int /*<<< orphan*/  lock_count; int /*<<< orphan*/  hloc32W; scalar_t__ text; } ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ LocalLock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_LockBuffer(EDITSTATE *es)
{
    if (!es->text)
    {
        if (!es->hloc32W)
            return;

        es->text = LocalLock(es->hloc32W);
    }

    es->lock_count++;
}