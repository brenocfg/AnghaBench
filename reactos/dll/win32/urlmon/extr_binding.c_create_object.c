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
struct TYPE_7__ {TYPE_1__* protocol; int /*<<< orphan*/  clsid; int /*<<< orphan*/  callback; int /*<<< orphan*/  mime; } ;
struct TYPE_6__ {int /*<<< orphan*/  IInternetProtocolEx_iface; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  TYPE_2__ Binding ;

/* Variables and functions */
 int /*<<< orphan*/  BINDSTATUS_BEGINSYNCOPERATION ; 
 int /*<<< orphan*/  BINDSTATUS_CLASSIDAVAILABLE ; 
 int /*<<< orphan*/  BINDSTATUS_ENDSYNCOPERATION ; 
 int /*<<< orphan*/  CLSID_NULL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IBindStatusCallback_OnProgress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IInternetProtocolEx_Terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/  create_mime_object (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_mime_clsid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_binding (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_object(Binding *binding)
{
    LPWSTR clsid_str;
    CLSID clsid;
    HRESULT hres;

    if(!binding->mime) {
        FIXME("MIME not available\n");
        return;
    }

    if((clsid_str = get_mime_clsid(binding->mime, &clsid)))
        IBindStatusCallback_OnProgress(binding->callback, 0, 0, BINDSTATUS_CLASSIDAVAILABLE, clsid_str);

    IBindStatusCallback_OnProgress(binding->callback, 0, 0, BINDSTATUS_BEGINSYNCOPERATION, NULL);

    if(clsid_str) {
        hres = create_mime_object(binding, &clsid, clsid_str);
        heap_free(clsid_str);
    }else {
        FIXME("Could not find object for MIME %s\n", debugstr_w(binding->mime));
        hres = REGDB_E_CLASSNOTREG;
    }

    IBindStatusCallback_OnProgress(binding->callback, 0, 0, BINDSTATUS_ENDSYNCOPERATION, NULL);
    binding->clsid = CLSID_NULL;

    stop_binding(binding, hres, NULL);
    if(FAILED(hres))
        IInternetProtocolEx_Terminate(&binding->protocol->IInternetProtocolEx_iface, 0);
}