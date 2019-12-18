#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  Completed; scalar_t__ BytesTransferred; int /*<<< orphan*/  BytesTotal; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {TYPE_5__* RemoteName; void* LocalName; } ;
struct TYPE_15__ {int ref; scalar_t__* tempFileName; scalar_t__ read_size; TYPE_4__* owner; TYPE_3__ fileProgress; TYPE_2__ IBackgroundCopyFile2_iface; TYPE_1__ info; } ;
struct TYPE_14__ {int /*<<< orphan*/  IBackgroundCopyJob3_iface; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ BackgroundCopyJobImpl ;
typedef  TYPE_5__ BackgroundCopyFileImpl ;

/* Variables and functions */
 int /*<<< orphan*/  BG_SIZE_UNKNOWN ; 
 int /*<<< orphan*/  BackgroundCopyFile2Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  IBackgroundCopyJob3_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 void* strdupW (int /*<<< orphan*/ ) ; 

HRESULT BackgroundCopyFileConstructor(BackgroundCopyJobImpl *owner,
                                      LPCWSTR remoteName, LPCWSTR localName,
                                      BackgroundCopyFileImpl **file)
{
    BackgroundCopyFileImpl *This;

    TRACE("(%s, %s, %p)\n", debugstr_w(remoteName), debugstr_w(localName), file);

    This = HeapAlloc(GetProcessHeap(), 0, sizeof *This);
    if (!This)
        return E_OUTOFMEMORY;

    This->info.RemoteName = strdupW(remoteName);
    if (!This->info.RemoteName)
    {
        HeapFree(GetProcessHeap(), 0, This);
        return E_OUTOFMEMORY;
    }

    This->info.LocalName = strdupW(localName);
    if (!This->info.LocalName)
    {
        HeapFree(GetProcessHeap(), 0, This->info.RemoteName);
        HeapFree(GetProcessHeap(), 0, This);
        return E_OUTOFMEMORY;
    }

    This->IBackgroundCopyFile2_iface.lpVtbl = &BackgroundCopyFile2Vtbl;
    This->ref = 1;

    This->fileProgress.BytesTotal = BG_SIZE_UNKNOWN;
    This->fileProgress.BytesTransferred = 0;
    This->fileProgress.Completed = FALSE;
    This->owner = owner;
    This->read_size = 0;
    This->tempFileName[0] = 0;
    IBackgroundCopyJob3_AddRef(&owner->IBackgroundCopyJob3_iface);

    *file = This;
    return S_OK;
}