#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  storageDirEntry; } ;
struct TYPE_24__ {TYPE_14__ base; } ;
typedef  TYPE_5__ TransactedSnapshotImpl ;
struct TYPE_21__ {int /*<<< orphan*/  lpVtbl; } ;
struct TYPE_20__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {int ref; int /*<<< orphan*/  storageDirEntry; int /*<<< orphan*/  openFlags; int /*<<< orphan*/  storageHead; int /*<<< orphan*/  strmHead; int /*<<< orphan*/ * baseVtbl; TYPE_2__ IPropertySetStorage_iface; TYPE_1__ IStorage_iface; } ;
struct TYPE_25__ {TYPE_7__* transactedParent; TYPE_5__* scratch; TYPE_4__ base; int /*<<< orphan*/  lastTransactionSig; } ;
typedef  TYPE_6__ TransactedSharedImpl ;
struct TYPE_27__ {int usVersion; int ulSectorSize; int /*<<< orphan*/ * pwcsTemplateFile; scalar_t__ reserved; } ;
struct TYPE_22__ {int /*<<< orphan*/  lpVtbl; } ;
struct TYPE_26__ {int /*<<< orphan*/  storageDirEntry; int /*<<< orphan*/  openFlags; TYPE_3__ IPropertySetStorage_iface; } ;
typedef  TYPE_7__ StorageBaseImpl ;
typedef  TYPE_8__ STGOPTIONS ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_6__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  IID_IStorage ; 
 int /*<<< orphan*/  IStorage_Commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STGC_DEFAULT ; 
 int /*<<< orphan*/  STGFMT_DOCFILE ; 
 int STGM_CREATE ; 
 int STGM_DELETEONRELEASE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_TRANSACTED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StgCreateStorageEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  StorageBaseImpl_CopyStorageTree (TYPE_14__*,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StorageBaseImpl_GetTransactionSig (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StorageBaseImpl_LockTransaction (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StorageBaseImpl_UnlockTransaction (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactedSharedImpl_BaseVtbl ; 
 int /*<<< orphan*/  TransactedSharedImpl_Vtbl ; 
 scalar_t__ impl_from_IStorage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT TransactedSharedImpl_Construct(StorageBaseImpl *parentStorage,
  TransactedSharedImpl** result)
{
  HRESULT hr;

  *result = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TransactedSharedImpl));
  if (*result)
  {
    IStorage *scratch;

    (*result)->base.IStorage_iface.lpVtbl = &TransactedSharedImpl_Vtbl;

    /* This is OK because the property set storage functions use the IStorage functions. */
    (*result)->base.IPropertySetStorage_iface.lpVtbl = parentStorage->IPropertySetStorage_iface.lpVtbl;
    (*result)->base.baseVtbl = &TransactedSharedImpl_BaseVtbl;

    list_init(&(*result)->base.strmHead);

    list_init(&(*result)->base.storageHead);

    (*result)->base.ref = 1;

    (*result)->base.openFlags = parentStorage->openFlags;

    hr = StorageBaseImpl_LockTransaction(parentStorage, FALSE);

    if (SUCCEEDED(hr))
    {
      STGOPTIONS stgo;

      /* This cannot fail, except with E_NOTIMPL in which case we don't care */
      StorageBaseImpl_GetTransactionSig(parentStorage, &(*result)->lastTransactionSig, FALSE);

      stgo.usVersion = 1;
      stgo.reserved = 0;
      stgo.ulSectorSize = 4096;
      stgo.pwcsTemplateFile = NULL;

      /* Create a new temporary storage to act as the scratch file. */
      hr = StgCreateStorageEx(NULL, STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_DELETEONRELEASE|STGM_TRANSACTED,
          STGFMT_DOCFILE, 0, &stgo, NULL, &IID_IStorage, (void**)&scratch);
      (*result)->scratch = (TransactedSnapshotImpl*)impl_from_IStorage(scratch);

      if (SUCCEEDED(hr))
      {
        hr = StorageBaseImpl_CopyStorageTree(&(*result)->scratch->base, (*result)->scratch->base.storageDirEntry,
          parentStorage, parentStorage->storageDirEntry);

        if (SUCCEEDED(hr))
        {
          hr = IStorage_Commit(scratch, STGC_DEFAULT);

          (*result)->base.storageDirEntry = (*result)->scratch->base.storageDirEntry;
          (*result)->transactedParent = parentStorage;
        }

        if (FAILED(hr))
          IStorage_Release(scratch);
      }

      StorageBaseImpl_UnlockTransaction(parentStorage, FALSE);
    }

    if (FAILED(hr)) HeapFree(GetProcessHeap(), 0, *result);

    return hr;
  }
  else
    return E_OUTOFMEMORY;
}