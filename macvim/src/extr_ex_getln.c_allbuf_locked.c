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
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ allbuf_lock ; 

int
allbuf_locked()
{
    if (allbuf_lock > 0)
    {
	EMSG(_("E811: Not allowed to change buffer information now"));
	return TRUE;
    }
    return FALSE;
}