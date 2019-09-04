#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int CMDLINE ; 
 int /*<<< orphan*/  FALSE ; 
 int INSERT ; 
 int State ; 
 scalar_t__ arrow_used ; 
 size_t curscript ; 
 int /*<<< orphan*/ ** scriptin ; 
 int /*<<< orphan*/  u_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
may_sync_undo()
{
    if ((!(State & (INSERT + CMDLINE)) || arrow_used)
					       && scriptin[curscript] == NULL)
	u_sync(FALSE);
}