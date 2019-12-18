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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  IStorage_iface; } ;
struct TYPE_7__ {TYPE_2__ base; } ;
typedef  TYPE_1__ StorageImpl ;
typedef  TYPE_2__ StorageBaseImpl ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  int /*<<< orphan*/  ILockBytes ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int STGM_TRANSACTED ; 
 int /*<<< orphan*/  StorageImpl_Construct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  Storage_ConstructTransacted (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static HRESULT Storage_Construct(
  HANDLE       hFile,
  LPCOLESTR    pwcsName,
  ILockBytes*  pLkbyt,
  DWORD        openFlags,
  BOOL         fileBased,
  BOOL         create,
  ULONG        sector_size,
  StorageBaseImpl** result)
{
  StorageImpl *newStorage;
  StorageBaseImpl *newTransactedStorage;
  HRESULT hr;

  hr = StorageImpl_Construct(hFile, pwcsName, pLkbyt, openFlags, fileBased, create, sector_size, &newStorage);
  if (FAILED(hr)) goto end;

  if (openFlags & STGM_TRANSACTED)
  {
    hr = Storage_ConstructTransacted(&newStorage->base, TRUE, &newTransactedStorage);
    if (FAILED(hr))
      IStorage_Release(&newStorage->base.IStorage_iface);
    else
      *result = newTransactedStorage;
  }
  else
    *result = &newStorage->base;

end:
  return hr;
}