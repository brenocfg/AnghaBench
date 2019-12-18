#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_6__ {scalar_t__ set_download; int /*<<< orphan*/  url; TYPE_2__* doc; } ;
typedef  TYPE_1__ download_proc_task_t ;
struct TYPE_7__ {scalar_t__ hostui; scalar_t__ view_sink; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  IDropTarget ;
typedef  TYPE_2__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IAdviseSink_OnViewChange (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDS_STATUS_DOWNLOADINGFROM ; 
 int /*<<< orphan*/  IDocHostUIHandler_GetDropTarget (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDropTarget_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_download_state (TYPE_2__*,int) ; 
 int /*<<< orphan*/  set_statustext (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_downloading_proc(task_t *_task)
{
    download_proc_task_t *task = (download_proc_task_t*)_task;
    HTMLDocumentObj *doc = task->doc;
    HRESULT hres;

    TRACE("(%p)\n", doc);

    set_statustext(doc, IDS_STATUS_DOWNLOADINGFROM, task->url);

    if(task->set_download)
        set_download_state(doc, 1);

    if(!doc->client)
        return;

    if(doc->view_sink)
        IAdviseSink_OnViewChange(doc->view_sink, DVASPECT_CONTENT, -1);

    if(doc->hostui) {
        IDropTarget *drop_target = NULL;

        hres = IDocHostUIHandler_GetDropTarget(doc->hostui, NULL /* FIXME */, &drop_target);
        if(SUCCEEDED(hres) && drop_target) {
            FIXME("Use IDropTarget\n");
            IDropTarget_Release(drop_target);
        }
    }
}