#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_7__ {scalar_t__ doc_navigate; int /*<<< orphan*/  IOleClientSite_iface; int /*<<< orphan*/ * document; } ;
typedef  scalar_t__ READYSTATE ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DocHost ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_HTMLDocument ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int /*<<< orphan*/  IOleObject_GetUserClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleObject_SetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ READYSTATE_COMPLETE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  advise_prop_notif (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_doc_ready_state (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  object_available_proc ; 
 int /*<<< orphan*/  object_available_task_destr ; 
 int /*<<< orphan*/  push_dochost_task (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_ready_state_task (TYPE_1__*,scalar_t__) ; 

HRESULT dochost_object_available(DocHost *This, IUnknown *doc)
{
    READYSTATE ready_state;
    task_header_t *task;
    IOleObject *oleobj;
    HRESULT hres;

    IUnknown_AddRef(doc);
    This->document = doc;

    hres = IUnknown_QueryInterface(doc, &IID_IOleObject, (void**)&oleobj);
    if(SUCCEEDED(hres)) {
        CLSID clsid;

        hres = IOleObject_GetUserClassID(oleobj, &clsid);
        if(SUCCEEDED(hres))
            TRACE("Got clsid %s\n",
                  IsEqualGUID(&clsid, &CLSID_HTMLDocument) ? "CLSID_HTMLDocument" : debugstr_guid(&clsid));

        hres = IOleObject_SetClientSite(oleobj, &This->IOleClientSite_iface);
        if(FAILED(hres))
            FIXME("SetClientSite failed: %08x\n", hres);

        IOleObject_Release(oleobj);
    }else {
        FIXME("Could not get IOleObject iface: %08x\n", hres);
    }

    /* FIXME: Call SetAdvise */

    task = heap_alloc(sizeof(*task));
    push_dochost_task(This, task, object_available_proc, object_available_task_destr, FALSE);

    hres = get_doc_ready_state(This, &ready_state);
    if(SUCCEEDED(hres)) {
        if(ready_state == READYSTATE_COMPLETE)
            push_ready_state_task(This, READYSTATE_COMPLETE);
        if(ready_state != READYSTATE_COMPLETE || This->doc_navigate)
            advise_prop_notif(This, TRUE);
    }else if(!This->doc_navigate) {
        /* If we can't get document's ready state, there is not much we can do.
         * Assume that document is complete at this point. */
        push_ready_state_task(This, READYSTATE_COMPLETE);
    }

    return S_OK;
}