#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ ILockBytes_iface; int /*<<< orphan*/ * pwcsName; int /*<<< orphan*/  flProtect; scalar_t__ hfile; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ ILockBytes ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_2__ FileLockBytesImpl ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FileLockBytesImpl_Vtbl ; 
 int /*<<< orphan*/  GetFullPathNameW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetProtectMode (int /*<<< orphan*/ ) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 

HRESULT FileLockBytesImpl_Construct(HANDLE hFile, DWORD openFlags, LPCWSTR pwcsName, ILockBytes **pLockBytes)
{
  FileLockBytesImpl *This;
  WCHAR fullpath[MAX_PATH];

  if (hFile == INVALID_HANDLE_VALUE)
    return E_FAIL;

  This = HeapAlloc(GetProcessHeap(), 0, sizeof(FileLockBytesImpl));

  if (!This)
    return E_OUTOFMEMORY;

  This->ILockBytes_iface.lpVtbl = &FileLockBytesImpl_Vtbl;
  This->ref = 1;
  This->hfile = hFile;
  This->flProtect = GetProtectMode(openFlags);

  if(pwcsName) {
    if (!GetFullPathNameW(pwcsName, MAX_PATH, fullpath, NULL))
    {
      lstrcpynW(fullpath, pwcsName, MAX_PATH);
    }
    This->pwcsName = HeapAlloc(GetProcessHeap(), 0,
                              (lstrlenW(fullpath)+1)*sizeof(WCHAR));
    if (!This->pwcsName)
    {
       HeapFree(GetProcessHeap(), 0, This);
       return E_OUTOFMEMORY;
    }
    lstrcpyW(This->pwcsName, fullpath);
  }
  else
    This->pwcsName = NULL;

  *pLockBytes = &This->ILockBytes_iface;

  return S_OK;
}