#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIEditingSession ;
typedef  int /*<<< orphan*/  nsIControllerContext ;
struct TYPE_9__ {int /*<<< orphan*/ * editor_controller; int /*<<< orphan*/ * editor; TYPE_3__* doc; scalar_t__ webbrowser; } ;
struct TYPE_7__ {TYPE_1__* window; } ;
struct TYPE_8__ {TYPE_2__ basedoc; } ;
struct TYPE_6__ {int /*<<< orphan*/  nswindow; } ;
typedef  TYPE_4__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIController ; 
 int /*<<< orphan*/  IID_nsIControllerContext ; 
 int /*<<< orphan*/  IID_nsIEditingSession ; 
 int /*<<< orphan*/  NS_EDITORCONTROLLER_CONTRACTID ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nsinterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIComponentManager_CreateInstanceByContractID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIControllerContext_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIControllerContext_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIControllerContext_SetCommandContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIController_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIEditingSession_GetEditorForWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIEditingSession_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIEditor_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pCompMgr ; 

void get_editor_controller(NSContainer *This)
{
    nsIEditingSession *editing_session = NULL;
    nsIControllerContext *ctrlctx;
    nsresult nsres;

    if(This->editor) {
        nsIEditor_Release(This->editor);
        This->editor = NULL;
    }

    if(This->editor_controller) {
        nsIController_Release(This->editor_controller);
        This->editor_controller = NULL;
    }

    nsres = get_nsinterface((nsISupports*)This->webbrowser, &IID_nsIEditingSession,
            (void**)&editing_session);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIEditingSession: %08x\n", nsres);
        return;
    }

    nsres = nsIEditingSession_GetEditorForWindow(editing_session,
            This->doc->basedoc.window->nswindow, &This->editor);
    nsIEditingSession_Release(editing_session);
    if(NS_FAILED(nsres)) {
        ERR("Could not get editor: %08x\n", nsres);
        return;
    }

    nsres = nsIComponentManager_CreateInstanceByContractID(pCompMgr,
            NS_EDITORCONTROLLER_CONTRACTID, NULL, &IID_nsIControllerContext, (void**)&ctrlctx);
    if(NS_SUCCEEDED(nsres)) {
        nsres = nsIControllerContext_SetCommandContext(ctrlctx, (nsISupports *)This->editor);
        if(NS_FAILED(nsres))
            ERR("SetCommandContext failed: %08x\n", nsres);
        nsres = nsIControllerContext_QueryInterface(ctrlctx, &IID_nsIController,
                (void**)&This->editor_controller);
        nsIControllerContext_Release(ctrlctx);
        if(NS_FAILED(nsres))
            ERR("Could not get nsIController interface: %08x\n", nsres);
    }else {
        ERR("Could not create edit controller: %08x\n", nsres);
    }
}