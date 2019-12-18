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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; int /*<<< orphan*/ * session; int /*<<< orphan*/ * installer; TYPE_1__ IActiveScriptSite_iface; } ;
typedef  TYPE_2__ MsiActiveScriptSite ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__**) ; 
 int /*<<< orphan*/  activescriptsitevtbl ; 
 TYPE_2__* msi_alloc (int) ; 

__attribute__((used)) static HRESULT create_activescriptsite(MsiActiveScriptSite **obj)
{
    MsiActiveScriptSite* object;

    TRACE("(%p)\n", obj);

    *obj = NULL;

    object = msi_alloc( sizeof(MsiActiveScriptSite) );
    if (!object)
        return E_OUTOFMEMORY;

    object->IActiveScriptSite_iface.lpVtbl = &activescriptsitevtbl;
    object->ref = 1;
    object->installer = NULL;
    object->session = NULL;

    *obj = object;

    return S_OK;
}