#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * curwin; int /*<<< orphan*/ * curbuf; int /*<<< orphan*/ * interp; } ;

/* Variables and functions */
 int /*<<< orphan*/  Tcl_DeleteInterp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_InterpDeleted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_Release (int /*<<< orphan*/ *) ; 
 TYPE_1__ tclinfo ; 

__attribute__((used)) static void
tcldelthisinterp()
{
    if (!Tcl_InterpDeleted(tclinfo.interp))
	Tcl_DeleteInterp(tclinfo.interp);
    Tcl_Release(tclinfo.interp);
    /* The interpreter is now gets deleted.  All registered commands (esp.
     * window and buffer commands) are deleted, triggering their deletion
     * callback, which deletes all refs pointing to this interpreter.
     * We could garbage-collect the unused ref structs in all windows and
     * buffers, but unless the user creates hundreds of sub-interpreters
     * all referring to lots of windows and buffers, this is hardly worth
     * the effort.  Unused refs are recycled by other interpreters, and
     * all refs are free'd when the window/buffer gets closed by vim.
     */

    tclinfo.interp = NULL;
    Tcl_Free(tclinfo.curbuf);
    Tcl_Free(tclinfo.curwin);
    tclinfo.curbuf = tclinfo.curwin = NULL;
}