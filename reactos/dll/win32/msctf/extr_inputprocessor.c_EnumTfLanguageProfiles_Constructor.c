#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int refCount; int /*<<< orphan*/  tipkey; int /*<<< orphan*/  catmgr; int /*<<< orphan*/  langid; TYPE_1__ IEnumTfLanguageProfiles_iface; } ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EnumTfLanguageProfiles ;

/* Variables and functions */
 int /*<<< orphan*/  CategoryMgr_Constructor (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnumTfLanguageProfilesVtbl ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  szwSystemTIPKey ; 

__attribute__((used)) static HRESULT EnumTfLanguageProfiles_Constructor(LANGID langid, EnumTfLanguageProfiles **out)
{
    HRESULT hr;
    EnumTfLanguageProfiles *This;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(EnumTfLanguageProfiles));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->IEnumTfLanguageProfiles_iface.lpVtbl= &EnumTfLanguageProfilesVtbl;
    This->refCount = 1;
    This->langid = langid;

    hr = CategoryMgr_Constructor(NULL,(IUnknown**)&This->catmgr);
    if (FAILED(hr))
    {
        HeapFree(GetProcessHeap(),0,This);
        return hr;
    }

    if (RegCreateKeyExW(HKEY_LOCAL_MACHINE, szwSystemTIPKey, 0, NULL, 0,
                    KEY_READ | KEY_WRITE, NULL, &This->tipkey, NULL) != ERROR_SUCCESS)
    {
        HeapFree(GetProcessHeap(), 0, This);
        return E_FAIL;
    }

    *out = This;
    TRACE("returning %p\n", *out);
    return S_OK;
}