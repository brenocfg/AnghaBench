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
struct stub_manager {int /*<<< orphan*/  object; int /*<<< orphan*/  oid; } ;
struct ifstub {int /*<<< orphan*/  ipid; } ;
struct TYPE_3__ {int cPublicRefs; int /*<<< orphan*/  ipid; int /*<<< orphan*/  oid; int /*<<< orphan*/  flags; int /*<<< orphan*/  oxid; } ;
typedef  TYPE_1__ STDOBJREF ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int MSHLFLAGS ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IRpcStubBuffer ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IPSFactoryBuffer_CreateStub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPSFactoryBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRpcStubBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MSHLFLAGS_NOPING ; 
 int MSHLFLAGS_TABLESTRONG ; 
 int MSHLFLAGS_TABLEWEAK ; 
 int NORMALEXTREFS ; 
 int /*<<< orphan*/  RPC_RegisterInterface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORFP_TABLEWEAK ; 
 int /*<<< orphan*/  SORF_NOPING ; 
 int /*<<< orphan*/  SORF_NULL ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apartment_createwindowifneeded (int /*<<< orphan*/ *) ; 
 scalar_t__ apartment_getoxid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 scalar_t__ get_facbuf_for_iid (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 struct stub_manager* get_stub_manager_from_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub_manager_ext_addref (struct stub_manager*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub_manager_ext_release (struct stub_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifstub* stub_manager_find_ifstub (struct stub_manager*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub_manager_int_release (struct stub_manager*) ; 
 struct ifstub* stub_manager_new_ifstub (struct stub_manager*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

HRESULT marshal_object(APARTMENT *apt, STDOBJREF *stdobjref, REFIID riid, IUnknown *object,
    DWORD dest_context, void *dest_context_data, MSHLFLAGS mshlflags)
{
    struct stub_manager *manager;
    struct ifstub       *ifstub;
    BOOL                 tablemarshal;
    HRESULT              hr;

    hr = apartment_getoxid(apt, &stdobjref->oxid);
    if (hr != S_OK)
        return hr;

    hr = apartment_createwindowifneeded(apt);
    if (hr != S_OK)
        return hr;

    if (!(manager = get_stub_manager_from_object(apt, object, TRUE)))
        return E_OUTOFMEMORY;

    stdobjref->flags = SORF_NULL;
    if (mshlflags & MSHLFLAGS_TABLEWEAK)
        stdobjref->flags |= SORFP_TABLEWEAK;
    if (mshlflags & MSHLFLAGS_NOPING)
        stdobjref->flags |= SORF_NOPING;
    stdobjref->oid = manager->oid;

    tablemarshal = ((mshlflags & MSHLFLAGS_TABLESTRONG) || (mshlflags & MSHLFLAGS_TABLEWEAK));

    /* make sure ifstub that we are creating is unique */
    ifstub = stub_manager_find_ifstub(manager, riid, mshlflags);
    if (!ifstub) {
        IRpcStubBuffer *stub = NULL;

        /* IUnknown doesn't require a stub buffer, because it never goes out on
         * the wire */
        if (!IsEqualIID(riid, &IID_IUnknown))
        {
            IPSFactoryBuffer *psfb;

            hr = get_facbuf_for_iid(riid, &psfb);
            if (hr == S_OK) {
                hr = IPSFactoryBuffer_CreateStub(psfb, riid, manager->object, &stub);
                IPSFactoryBuffer_Release(psfb);
                if (hr != S_OK)
                    ERR("Failed to create an IRpcStubBuffer from IPSFactory for %s with error 0x%08x\n",
                        debugstr_guid(riid), hr);
            }else {
                ERR("couldn't get IPSFactory buffer for interface %s\n", debugstr_guid(riid));
                hr = E_NOINTERFACE;
            }

        }

        if (hr == S_OK) {
            ifstub = stub_manager_new_ifstub(manager, stub, riid, dest_context, dest_context_data, mshlflags);
            if (!ifstub)
                hr = E_OUTOFMEMORY;
        }
        if (stub) IRpcStubBuffer_Release(stub);

        if (hr != S_OK) {
            stub_manager_int_release(manager);
            /* destroy the stub manager if it has no ifstubs by releasing
             * zero external references */
            stub_manager_ext_release(manager, 0, FALSE, TRUE);
            return hr;
        }
    }

    if (!tablemarshal)
    {
        stdobjref->cPublicRefs = NORMALEXTREFS;
        stub_manager_ext_addref(manager, stdobjref->cPublicRefs, FALSE);
    }
    else
    {
        stdobjref->cPublicRefs = 0;
        if (mshlflags & MSHLFLAGS_TABLESTRONG)
            stub_manager_ext_addref(manager, 1, FALSE);
        else
            stub_manager_ext_addref(manager, 0, TRUE);
    }

    /* FIXME: check return value */
    RPC_RegisterInterface(riid);

    stdobjref->ipid = ifstub->ipid;

    stub_manager_int_release(manager);
    return S_OK;
}