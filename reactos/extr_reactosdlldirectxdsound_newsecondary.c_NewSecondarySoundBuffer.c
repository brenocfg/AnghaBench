#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int ULONG ;
struct TYPE_9__ {int cbSize; int wBitsPerSample; int /*<<< orphan*/  nSamplesPerSec; } ;
struct TYPE_8__ {int dwBufferBytes; TYPE_6__* lpwfxFormat; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_7__ {int ref; int BufferSize; int /*<<< orphan*/ * lpVtbl; struct TYPE_7__* Format; scalar_t__ PrimaryBuffer; scalar_t__ Position; scalar_t__ Flags; int /*<<< orphan*/  VolumePan; int /*<<< orphan*/  Volume; int /*<<< orphan*/  State; int /*<<< orphan*/  dwFrequency; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  dwLevel; int /*<<< orphan*/  Filter; void* Buffer; } ;
typedef  int /*<<< orphan*/  LPFILTERINFO ;
typedef  scalar_t__ LPDIRECTSOUNDBUFFER8 ;
typedef  TYPE_1__* LPCDirectSoundBuffer ;
typedef  TYPE_2__* LPCDSBUFFERDESC ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CDirectSoundBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CopyMemory (TYPE_1__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  DSBPAN_CENTER ; 
 int /*<<< orphan*/  DSBVOLUME_MAX ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  FillMemory (void*,int,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KSSTATE_STOP ; 
 int /*<<< orphan*/  vt_DirectSoundBuffer8 ; 

HRESULT
NewSecondarySoundBuffer(
    LPDIRECTSOUNDBUFFER8 *OutBuffer,
    LPFILTERINFO Filter,
    DWORD dwLevel,
    LPCDSBUFFERDESC lpcDSBufferDesc,
    LPDIRECTSOUNDBUFFER8 PrimaryBuffer)
{
    ULONG FormatSize;
    LPCDirectSoundBuffer This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CDirectSoundBuffer));

    if (!This)
    {
        /* not enough memory */
        return DSERR_OUTOFMEMORY;
    }

    FormatSize = sizeof(WAVEFORMATEX) + lpcDSBufferDesc->lpwfxFormat->cbSize;

    This->Format = HeapAlloc(GetProcessHeap(), 0, FormatSize);
    if (!This->Format)
    {
        /* not enough memory */
        HeapFree(GetProcessHeap(), 0, This);
        return DSERR_OUTOFMEMORY;
    }

    /* sanity check */
    ASSERT(lpcDSBufferDesc->dwBufferBytes);

    /* allocate sound buffer */
    This->Buffer = HeapAlloc(GetProcessHeap(), 0, lpcDSBufferDesc->dwBufferBytes);
    if (!This->Buffer)
    {
        /* not enough memory */
        HeapFree(GetProcessHeap(), 0, This->Format);
        HeapFree(GetProcessHeap(), 0, This);
        return DSERR_OUTOFMEMORY;
    }

    /* fill buffer with silence */
    FillMemory(This->Buffer, lpcDSBufferDesc->dwBufferBytes, lpcDSBufferDesc->lpwfxFormat->wBitsPerSample == 8 ? 0x80 : 0);

    This->ref = 1;
    This->lpVtbl = &vt_DirectSoundBuffer8;
    This->Filter = Filter;
    This->dwLevel = dwLevel;
    This->dwFlags = lpcDSBufferDesc->dwFlags;
    This->dwFrequency = lpcDSBufferDesc->lpwfxFormat->nSamplesPerSec;
    This->State = KSSTATE_STOP;
    This->Volume = DSBVOLUME_MAX;
    This->VolumePan = DSBPAN_CENTER;
    This->Flags = 0;
    This->Position = 0;
    This->BufferSize = lpcDSBufferDesc->dwBufferBytes;
    This->PrimaryBuffer = PrimaryBuffer;

    CopyMemory(This->Format, lpcDSBufferDesc->lpwfxFormat, FormatSize);

    *OutBuffer = (LPDIRECTSOUNDBUFFER8)&This->lpVtbl;
    return DS_OK;
}