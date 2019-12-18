#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ipidRemUnknown; } ;
struct proxy_manager {int sorflags; int /*<<< orphan*/  cs; int /*<<< orphan*/ * remunk; TYPE_4__ oxid_info; int /*<<< orphan*/  dest_context_data; int /*<<< orphan*/  dest_context; int /*<<< orphan*/  oxid; TYPE_1__* parent; } ;
struct apartment {scalar_t__ oxid; } ;
struct TYPE_6__ {int flags; int cPublicRefs; int /*<<< orphan*/  ipid; scalar_t__ oid; int /*<<< orphan*/  oxid; } ;
struct TYPE_5__ {scalar_t__ oxid; } ;
typedef  TYPE_2__ STDOBJREF ;
typedef  scalar_t__ OID ;
typedef  int /*<<< orphan*/  IRemUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CO_E_NOTINITIALIZED ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IRemUnknown ; 
 int /*<<< orphan*/  IRemUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int SORFP_NOLIFETIMEMGMT ; 
 int SORF_NOPING ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct apartment* apartment_get_current_or_mta () ; 
 int /*<<< orphan*/  apartment_release (struct apartment*) ; 
 scalar_t__ unmarshal_object (TYPE_2__*,struct apartment*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,void**) ; 

__attribute__((used)) static HRESULT proxy_manager_get_remunknown(struct proxy_manager * This, IRemUnknown **remunk)
{
    HRESULT hr = S_OK;
    struct apartment *apt;
    BOOL called_in_original_apt;

    /* we don't want to try and unmarshal or use IRemUnknown if we don't want
     * lifetime management */
    if (This->sorflags & SORFP_NOLIFETIMEMGMT)
        return S_FALSE;

    if (!(apt = apartment_get_current_or_mta()))
        return CO_E_NOTINITIALIZED;

    called_in_original_apt = This->parent && (This->parent->oxid == apt->oxid);

    EnterCriticalSection(&This->cs);
    /* only return the cached object if called from the original apartment.
     * in future, we might want to make the IRemUnknown proxy callable from any
     * apartment to avoid these checks */
    if (This->remunk && called_in_original_apt)
    {
        /* already created - return existing object */
        *remunk = This->remunk;
        IRemUnknown_AddRef(*remunk);
    }
    else if (!This->parent)
    {
        /* disconnected - we can't create IRemUnknown */
        *remunk = NULL;
        hr = S_FALSE;
    }
    else
    {
        STDOBJREF stdobjref;
        /* Don't want IRemUnknown lifetime management as this is IRemUnknown!
         * We also don't care about whether or not the stub is still alive */
        stdobjref.flags = SORFP_NOLIFETIMEMGMT | SORF_NOPING;
        stdobjref.cPublicRefs = 1;
        /* oxid of destination object */
        stdobjref.oxid = This->oxid;
        /* FIXME: what should be used for the oid? The DCOM draft doesn't say */
        stdobjref.oid = (OID)-1;
        stdobjref.ipid = This->oxid_info.ipidRemUnknown;

        /* do the unmarshal */
        hr = unmarshal_object(&stdobjref, apt, This->dest_context,
                              This->dest_context_data, &IID_IRemUnknown,
                              &This->oxid_info, (void**)remunk);
        if (hr == S_OK && called_in_original_apt)
        {
            This->remunk = *remunk;
            IRemUnknown_AddRef(This->remunk);
        }
    }
    LeaveCriticalSection(&This->cs);
    apartment_release(apt);

    TRACE("got IRemUnknown* pointer %p, hr = 0x%08x\n", *remunk, hr);

    return hr;
}