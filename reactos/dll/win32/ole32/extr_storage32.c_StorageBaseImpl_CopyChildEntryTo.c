#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {scalar_t__ stgType; scalar_t__ leftChild; scalar_t__ rightChild; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbSize; } ;
struct TYPE_7__ {int /*<<< orphan*/  IStream_iface; } ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  TYPE_1__ StgStreamImpl ;
typedef  TYPE_2__ STATSTG ;
typedef  int /*<<< orphan*/ ** SNB ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DirRef ;
typedef  TYPE_3__ DirEntry ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DIRENTRY_NULL ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IStorage_CreateStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_CreateStream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IStorage_OpenStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_SetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Stat (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int STGM_CREATE ; 
 int STGM_FAILIFTHERE ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 scalar_t__ STGTY_STORAGE ; 
 scalar_t__ STGTY_STREAM ; 
 scalar_t__ STG_E_FILEALREADYEXISTS ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 TYPE_1__* StgStreamImpl_Construct (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ StorageBaseImpl_CopyStorageEntryTo (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ StorageBaseImpl_ReadDirEntry (int /*<<< orphan*/ *,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT StorageBaseImpl_CopyChildEntryTo(StorageBaseImpl *This,
    DirRef srcEntry, BOOL skip_storage, BOOL skip_stream,
    SNB snbExclude, IStorage *pstgDest)
{
  DirEntry data;
  HRESULT hr;
  BOOL skip = FALSE;
  IStorage *pstgTmp;
  IStream *pstrChild, *pstrTmp;
  STATSTG strStat;

  if (srcEntry == DIRENTRY_NULL)
    return S_OK;

  hr = StorageBaseImpl_ReadDirEntry( This, srcEntry, &data );

  if (FAILED(hr))
    return hr;

  if ( snbExclude )
  {
    WCHAR **snb = snbExclude;

    while ( *snb != NULL && !skip )
    {
      if ( wcscmp(data.name, *snb) == 0 )
        skip = TRUE;
      ++snb;
    }
  }

  if (!skip)
  {
    if (data.stgType == STGTY_STORAGE && !skip_storage)
    {
      /*
       * create a new storage in destination storage
       */
      hr = IStorage_CreateStorage( pstgDest, data.name,
                                   STGM_FAILIFTHERE|STGM_WRITE|STGM_SHARE_EXCLUSIVE,
                                   0, 0,
                                   &pstgTmp );

      /*
       * if it already exist, don't create a new one use this one
       */
      if (hr == STG_E_FILEALREADYEXISTS)
      {
        hr = IStorage_OpenStorage( pstgDest, data.name, NULL,
                                   STGM_WRITE|STGM_SHARE_EXCLUSIVE,
                                   NULL, 0, &pstgTmp );
      }

      if (SUCCEEDED(hr))
      {
        hr = StorageBaseImpl_CopyStorageEntryTo( This, srcEntry, skip_storage,
                                                 skip_stream, NULL, pstgTmp );

        IStorage_Release(pstgTmp);
      }
    }
    else if (data.stgType == STGTY_STREAM && !skip_stream)
    {
      /*
       * create a new stream in destination storage. If the stream already
       * exist, it will be deleted and a new one will be created.
       */
      hr = IStorage_CreateStream( pstgDest, data.name,
                                  STGM_CREATE|STGM_WRITE|STGM_SHARE_EXCLUSIVE,
                                  0, 0, &pstrTmp );

      /*
       * open child stream storage. This operation must succeed even if the
       * stream is already open, so we use internal functions to do it.
       */
      if (hr == S_OK)
      {
        StgStreamImpl *streamimpl = StgStreamImpl_Construct(This, STGM_READ|STGM_SHARE_EXCLUSIVE, srcEntry);

        if (streamimpl)
        {
          pstrChild = &streamimpl->IStream_iface;
          if (pstrChild)
            IStream_AddRef(pstrChild);
        }
        else
        {
          pstrChild = NULL;
          hr = E_OUTOFMEMORY;
        }
      }

      if (hr == S_OK)
      {
        /*
         * Get the size of the source stream
         */
        IStream_Stat( pstrChild, &strStat, STATFLAG_NONAME );

        /*
         * Set the size of the destination stream.
         */
        IStream_SetSize(pstrTmp, strStat.cbSize);

        /*
         * do the copy
         */
        hr = IStream_CopyTo( pstrChild, pstrTmp, strStat.cbSize,
                             NULL, NULL );

        IStream_Release( pstrChild );
      }

      IStream_Release( pstrTmp );
    }
  }

  /* copy siblings */
  if (SUCCEEDED(hr))
    hr = StorageBaseImpl_CopyChildEntryTo( This, data.leftChild, skip_storage,
                                           skip_stream, snbExclude, pstgDest );

  if (SUCCEEDED(hr))
    hr = StorageBaseImpl_CopyChildEntryTo( This, data.rightChild, skip_storage,
                                           skip_stream, snbExclude, pstgDest );

  TRACE("<-- %08x\n", hr);
  return hr;
}