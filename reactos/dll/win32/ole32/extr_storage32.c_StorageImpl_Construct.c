#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int openFlags; int ref; TYPE_10__ IStorage_iface; int /*<<< orphan*/  reverted; int /*<<< orphan*/  lockingrole; int /*<<< orphan*/  create; int /*<<< orphan*/ * baseVtbl; TYPE_2__ IDirectWriterLock_iface; TYPE_1__ IPropertySetStorage_iface; int /*<<< orphan*/  storageHead; int /*<<< orphan*/  strmHead; } ;
struct TYPE_17__ {int /*<<< orphan*/  grfLocksSupported; } ;
struct TYPE_16__ {TYPE_8__ base; int /*<<< orphan*/  locks_supported; int /*<<< orphan*/ * lockBytes; int /*<<< orphan*/  smallBlockSize; int /*<<< orphan*/  bigBlockSize; } ;
typedef  TYPE_3__ StorageImpl ;
typedef  TYPE_4__ STATSTG ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  int /*<<< orphan*/  ILockBytes ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_SMALL_BLOCK_SIZE ; 
 int /*<<< orphan*/  DirectWriterLockVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileLockBytesImpl_Construct (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILockBytes_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILockBytes_Stat (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPropertySetStorage_Vtbl ; 
 int /*<<< orphan*/  IStorage_Release (TYPE_10__*) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int STGM_CREATE ; 
 int STGM_DIRECT_SWMR ; 
 int STGM_READ ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_DENY_NONE ; 
 int STGM_SHARE_DENY_WRITE ; 
 int /*<<< orphan*/  STG_E_INVALIDFLAG ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWMR_None ; 
 int /*<<< orphan*/  SWMR_Reader ; 
 int /*<<< orphan*/  SWMR_Writer ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StorageImpl_BaseVtbl ; 
 int /*<<< orphan*/  StorageImpl_Flush (TYPE_8__*) ; 
 int /*<<< orphan*/  StorageImpl_GrabLocks (TYPE_3__*,int) ; 
 int /*<<< orphan*/  StorageImpl_Refresh (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StorageImpl_Vtbl ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_LOCK_READ ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  validateSTGM (int) ; 

__attribute__((used)) static HRESULT StorageImpl_Construct(
  HANDLE       hFile,
  LPCOLESTR    pwcsName,
  ILockBytes*  pLkbyt,
  DWORD        openFlags,
  BOOL         fileBased,
  BOOL         create,
  ULONG        sector_size,
  StorageImpl** result)
{
  StorageImpl* This;
  HRESULT hr = S_OK;
  STATSTG stat;

  if ( FAILED( validateSTGM(openFlags) ))
    return STG_E_INVALIDFLAG;

  This = HeapAlloc(GetProcessHeap(), 0, sizeof(StorageImpl));
  if (!This)
    return E_OUTOFMEMORY;

  memset(This, 0, sizeof(StorageImpl));

  list_init(&This->base.strmHead);

  list_init(&This->base.storageHead);

  This->base.IStorage_iface.lpVtbl = &StorageImpl_Vtbl;
  This->base.IPropertySetStorage_iface.lpVtbl = &IPropertySetStorage_Vtbl;
  This->base.IDirectWriterLock_iface.lpVtbl = &DirectWriterLockVtbl;
  This->base.baseVtbl = &StorageImpl_BaseVtbl;
  This->base.openFlags = (openFlags & ~STGM_CREATE);
  This->base.ref = 1;
  This->base.create = create;

  if (openFlags == (STGM_DIRECT_SWMR|STGM_READWRITE|STGM_SHARE_DENY_WRITE))
    This->base.lockingrole = SWMR_Writer;
  else if (openFlags == (STGM_DIRECT_SWMR|STGM_READ|STGM_SHARE_DENY_NONE))
    This->base.lockingrole = SWMR_Reader;
  else
    This->base.lockingrole = SWMR_None;

  This->base.reverted = FALSE;

  /*
   * Initialize the big block cache.
   */
  This->bigBlockSize   = sector_size;
  This->smallBlockSize = DEF_SMALL_BLOCK_SIZE;
  if (hFile)
    hr = FileLockBytesImpl_Construct(hFile, openFlags, pwcsName, &This->lockBytes);
  else
  {
    This->lockBytes = pLkbyt;
    ILockBytes_AddRef(pLkbyt);
  }

  if (SUCCEEDED(hr))
    hr = ILockBytes_Stat(This->lockBytes, &stat, STATFLAG_NONAME);

  if (SUCCEEDED(hr))
  {
    This->locks_supported = stat.grfLocksSupported;
    if (!hFile)
        /* Don't try to use wine-internal locking flag with custom ILockBytes */
        This->locks_supported &= ~WINE_LOCK_READ;

    hr = StorageImpl_GrabLocks(This, openFlags);
  }

  if (SUCCEEDED(hr))
    hr = StorageImpl_Refresh(This, TRUE, create);

  if (FAILED(hr))
  {
    IStorage_Release(&This->base.IStorage_iface);
    *result = NULL;
  }
  else
  {
    StorageImpl_Flush(&This->base);
    *result = This;
  }

  return hr;
}