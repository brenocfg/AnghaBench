#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsICommandParams ;
typedef  int /*<<< orphan*/  nsICommandManager ;
struct TYPE_10__ {TYPE_1__* window; TYPE_3__* doc_obj; } ;
struct TYPE_9__ {TYPE_2__* nscontainer; } ;
struct TYPE_8__ {scalar_t__ webbrowser; } ;
struct TYPE_7__ {int /*<<< orphan*/  nswindow; } ;
typedef  TYPE_4__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IID_nsICommandManager ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 int /*<<< orphan*/  get_nsinterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsICommandManager_DoCommand (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsICommandManager_Release (int /*<<< orphan*/ *) ; 

void do_ns_command(HTMLDocument *This, const char *cmd, nsICommandParams *nsparam)
{
    nsICommandManager *cmdmgr;
    nsresult nsres;

    TRACE("(%p)\n", This);

    if(!This->doc_obj || !This->doc_obj->nscontainer)
        return;

    nsres = get_nsinterface((nsISupports*)This->doc_obj->nscontainer->webbrowser, &IID_nsICommandManager, (void**)&cmdmgr);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsICommandManager: %08x\n", nsres);
        return;
    }

    nsres = nsICommandManager_DoCommand(cmdmgr, cmd, nsparam, This->window->nswindow);
    if(NS_FAILED(nsres))
        ERR("DoCommand(%s) failed: %08x\n", debugstr_a(cmd), nsres);

    nsICommandManager_Release(cmdmgr);
}