#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_1__ IDirectMusicDownload_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ IDirectMusicDownloadImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  DMUSIC_LockModule () ; 
 int /*<<< orphan*/  DirectMusicDownload_Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT DMUSIC_CreateDirectMusicDownloadImpl(const GUID *guid, void **ret_iface, IUnknown *unk_outer)
{
    IDirectMusicDownloadImpl *download;

    download = HeapAlloc(GetProcessHeap(), 0, sizeof(*download));
    if (!download)
    {
        *ret_iface = NULL;
        return E_OUTOFMEMORY;
    }

    download->IDirectMusicDownload_iface.lpVtbl = &DirectMusicDownload_Vtbl;
    download->ref = 1;
    *ret_iface = download;

    DMUSIC_LockModule();
    return S_OK;
}