#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int refs; int /*<<< orphan*/  entry; void* DllGetClassObject; void* DllCanUnloadNow; scalar_t__ library; void* library_name; } ;
typedef  TYPE_1__ OpenDll ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  void* DllGetClassObjectFunc ;
typedef  void* DllCanUnloadNowFunc ;

/* Variables and functions */
 TYPE_1__* COMPOBJ_DllList_Get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CO_E_DLLNOTFOUND ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ACCESSDENIED ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LOAD_WITH_ALTERED_SEARCH_PATH ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadLibraryExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csOpenDllList ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openDllList ; 

__attribute__((used)) static HRESULT COMPOBJ_DllList_Add(LPCWSTR library_name, OpenDll **ret)
{
    OpenDll *entry;
    int len;
    HRESULT hr = S_OK;
    HANDLE hLibrary;
    DllCanUnloadNowFunc DllCanUnloadNow;
    DllGetClassObjectFunc DllGetClassObject;

    TRACE("%s\n", debugstr_w(library_name));

    *ret = COMPOBJ_DllList_Get(library_name);
    if (*ret) return S_OK;

    /* do this outside the csOpenDllList to avoid creating a lock dependency on
     * the loader lock */
    hLibrary = LoadLibraryExW(library_name, 0, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!hLibrary)
    {
        ERR("couldn't load in-process dll %s\n", debugstr_w(library_name));
        /* failure: DLL could not be loaded */
        return E_ACCESSDENIED; /* FIXME: or should this be CO_E_DLLNOTFOUND? */
    }

    DllCanUnloadNow = (void *)GetProcAddress(hLibrary, "DllCanUnloadNow");
    /* Note: failing to find DllCanUnloadNow is not a failure */
    DllGetClassObject = (void *)GetProcAddress(hLibrary, "DllGetClassObject");
    if (!DllGetClassObject)
    {
        /* failure: the dll did not export DllGetClassObject */
        ERR("couldn't find function DllGetClassObject in %s\n", debugstr_w(library_name));
        FreeLibrary(hLibrary);
        return CO_E_DLLNOTFOUND;
    }

    EnterCriticalSection( &csOpenDllList );

    *ret = COMPOBJ_DllList_Get(library_name);
    if (*ret)
    {
        /* another caller to this function already added the dll while we
         * weren't in the critical section */
        FreeLibrary(hLibrary);
    }
    else
    {
        len = lstrlenW(library_name);
        entry = HeapAlloc(GetProcessHeap(),0, sizeof(OpenDll));
        if (entry)
            entry->library_name = HeapAlloc(GetProcessHeap(), 0, (len + 1)*sizeof(WCHAR));
        if (entry && entry->library_name)
        {
            memcpy(entry->library_name, library_name, (len + 1)*sizeof(WCHAR));
            entry->library = hLibrary;
            entry->refs = 1;
            entry->DllCanUnloadNow = DllCanUnloadNow;
            entry->DllGetClassObject = DllGetClassObject;
            list_add_tail(&openDllList, &entry->entry);
            *ret = entry;
        }
        else
        {
            HeapFree(GetProcessHeap(), 0, entry);
            hr = E_OUTOFMEMORY;
            FreeLibrary(hLibrary);
        }
    }

    LeaveCriticalSection( &csOpenDllList );

    return hr;
}