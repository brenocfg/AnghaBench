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
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
struct TYPE_4__ {int cbSize; int nChannels; int nSamplesPerSec; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_5__ {int ref; int /*<<< orphan*/ * lpVtbl; int /*<<< orphan*/  Lock; TYPE_1__ Format; int /*<<< orphan*/ * hPin; int /*<<< orphan*/  VolumePan; int /*<<< orphan*/  Volume; scalar_t__ dwFrequency; void* dwFlags; void* dwLevel; int /*<<< orphan*/  Filter; } ;
typedef  int /*<<< orphan*/  LPFILTERINFO ;
typedef  scalar_t__ LPDIRECTSOUNDBUFFER8 ;
typedef  TYPE_2__* LPCDirectSoundBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  void* DWORD ;
typedef  int /*<<< orphan*/  CDirectSoundBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  DSBPAN_CENTER ; 
 int /*<<< orphan*/  DSBVOLUME_MAX ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  vt_DirectSoundBuffer8 ; 

HRESULT
NewPrimarySoundBuffer(
    LPDIRECTSOUNDBUFFER8 *OutBuffer,
    LPFILTERINFO Filter,
    DWORD dwLevel,
    DWORD dwFlags)
{
    LPCDirectSoundBuffer This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CDirectSoundBuffer));

    if (!This)
    {
        /* not enough memory */
        return DSERR_OUTOFMEMORY;
    }

    This->ref = 1;
    This->lpVtbl = &vt_DirectSoundBuffer8;
    This->Filter = Filter;
    This->dwLevel = dwLevel;
    This->dwFlags = dwFlags;
    This->dwFrequency = 0;
    This->Volume = DSBVOLUME_MAX;
    This->VolumePan = DSBPAN_CENTER;
    This->hPin = NULL;

    /* FIXME: determine default format for audio device */
    This->Format.cbSize = sizeof(WAVEFORMATEX);
    This->Format.nChannels = 2;
    This->Format.nSamplesPerSec = 44100;
    This->Format.wBitsPerSample = 16;
    This->Format.wFormatTag = WAVE_FORMAT_PCM;
    This->Format.nBlockAlign = (This->Format.nChannels * This->Format.wBitsPerSample) / 8;
    This->Format.nAvgBytesPerSec = (This->Format.nChannels * This->Format.nSamplesPerSec * This->Format.wBitsPerSample) / 8;

    InitializeCriticalSection(&This->Lock);

    *OutBuffer = (LPDIRECTSOUNDBUFFER8)&This->lpVtbl;
    return DS_OK;
}