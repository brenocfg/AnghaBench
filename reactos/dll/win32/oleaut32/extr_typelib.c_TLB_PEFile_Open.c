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
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int refs; TYPE_2__ IUnknown_iface; int /*<<< orphan*/ * typelib_base; int /*<<< orphan*/ * typelib_resource; int /*<<< orphan*/ * dll; int /*<<< orphan*/ * typelib_global; } ;
typedef  TYPE_1__ TLB_PEFile ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_2__ IUnknown ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int DONT_RESOLVE_DLL_REFERENCES ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/ * FindResourceW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int LOAD_LIBRARY_AS_DATAFILE ; 
 int LOAD_WITH_ALTERED_SEARCH_PATH ; 
 int /*<<< orphan*/ * LoadLibraryExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * LoadResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LockResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLB_PEFile_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  TLB_PEFile_Vtable ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TYPE_E_CANTLOADLIBRARY ; 
 TYPE_1__* heap_alloc (int) ; 

__attribute__((used)) static HRESULT TLB_PEFile_Open(LPCWSTR path, INT index, LPVOID *ppBase, DWORD *pdwTLBLength, IUnknown **ppFile)
{
    TLB_PEFile *This;
    HRESULT hr = TYPE_E_CANTLOADLIBRARY;

    This = heap_alloc(sizeof(TLB_PEFile));
    if (!This)
        return E_OUTOFMEMORY;

    This->IUnknown_iface.lpVtbl = &TLB_PEFile_Vtable;
    This->refs = 1;
    This->dll = NULL;
    This->typelib_resource = NULL;
    This->typelib_global = NULL;
    This->typelib_base = NULL;

    This->dll = LoadLibraryExW(path, 0, DONT_RESOLVE_DLL_REFERENCES |
                    LOAD_LIBRARY_AS_DATAFILE | LOAD_WITH_ALTERED_SEARCH_PATH);

    if (This->dll)
    {
        static const WCHAR TYPELIBW[] = {'T','Y','P','E','L','I','B',0};
        This->typelib_resource = FindResourceW(This->dll, MAKEINTRESOURCEW(index), TYPELIBW);
        if (This->typelib_resource)
        {
            This->typelib_global = LoadResource(This->dll, This->typelib_resource);
            if (This->typelib_global)
            {
                This->typelib_base = LockResource(This->typelib_global);

                if (This->typelib_base)
                {
                    *pdwTLBLength = SizeofResource(This->dll, This->typelib_resource);
                    *ppBase = This->typelib_base;
                    *ppFile = &This->IUnknown_iface;
                    return S_OK;
                }
            }
        }

        TRACE("No TYPELIB resource found\n");
        hr = E_FAIL;
    }

    TLB_PEFile_Release(&This->IUnknown_iface);
    return hr;
}