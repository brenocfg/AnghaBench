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
struct TYPE_3__ {int /*<<< orphan*/ * pDS8; int /*<<< orphan*/ * pDS; int /*<<< orphan*/ * pUnknown; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ LPDIRECTSOUND8 ;
typedef  TYPE_1__ IDirectSoundImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IDirectSound8_IDirectSound8_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound8_IDirectSound8_Create (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirectSound8_IDirectSound_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound8_IDirectSound_Create (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirectSound8_IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound8_IUnknown_Create (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IDirectSound ; 
 int /*<<< orphan*/  IID_IDirectSound8 ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT DSOUND_QueryInterface8(
    LPDIRECTSOUND8 iface,
    REFIID riid,
    LPVOID * ppobj)
{
    IDirectSoundImpl *This = (IDirectSoundImpl *)iface;
    TRACE("(%p,%s,%p)\n",This,debugstr_guid(riid),ppobj);

    if (ppobj == NULL) {
        WARN("invalid parameter\n");
        return E_INVALIDARG;
    }

    if (IsEqualIID(riid, &IID_IUnknown)) {
        if (!This->pUnknown) {
            IDirectSound8_IUnknown_Create(iface, &This->pUnknown);
            if (!This->pUnknown) {
                WARN("IDirectSound8_IUnknown_Create() failed\n");
                *ppobj = NULL;
                return E_NOINTERFACE;
            }
        }
        IDirectSound8_IUnknown_AddRef(This->pUnknown);
        *ppobj = This->pUnknown;
        return S_OK;
    } else if (IsEqualIID(riid, &IID_IDirectSound)) {
        if (!This->pDS) {
            IDirectSound8_IDirectSound_Create(iface, &This->pDS);
            if (!This->pDS) {
                WARN("IDirectSound8_IDirectSound_Create() failed\n");
                *ppobj = NULL;
                return E_NOINTERFACE;
            }
        }
        IDirectSound8_IDirectSound_AddRef(This->pDS);
        *ppobj = This->pDS;
        return S_OK;
    } else if (IsEqualIID(riid, &IID_IDirectSound8)) {
        if (!This->pDS8) {
            IDirectSound8_IDirectSound8_Create(iface, &This->pDS8);
            if (!This->pDS8) {
                WARN("IDirectSound8_IDirectSound8_Create() failed\n");
                *ppobj = NULL;
                return E_NOINTERFACE;
            }
        }
        IDirectSound8_IDirectSound8_AddRef(This->pDS8);
        *ppobj = This->pDS8;
        return S_OK;
    }

    *ppobj = NULL;
    WARN("Unknown IID %s\n",debugstr_guid(riid));
    return E_NOINTERFACE;
}