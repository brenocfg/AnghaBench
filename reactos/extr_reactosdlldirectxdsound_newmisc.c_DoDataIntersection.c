#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
struct TYPE_18__ {int nAvgBytesPerSec; int wBitsPerSample; int nSamplesPerSec; int nChannels; int /*<<< orphan*/  wFormatTag; int /*<<< orphan*/  nBlockAlign; scalar_t__ cbSize; } ;
struct TYPE_14__ {int nSamplesPerSec; int nChannels; int nAvgBytesPerSec; int wBitsPerSample; scalar_t__ cbSize; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_13__ {int FormatSize; int SampleSize; int /*<<< orphan*/  Specifier; int /*<<< orphan*/  SubFormat; int /*<<< orphan*/  MajorFormat; scalar_t__ Reserved; scalar_t__ Flags; } ;
struct TYPE_17__ {TYPE_3__ WaveFormatEx; TYPE_2__ DataFormat; } ;
struct TYPE_16__ {int Count; int Size; } ;
struct TYPE_12__ {int /*<<< orphan*/  Id; int /*<<< orphan*/  Set; int /*<<< orphan*/  Flags; } ;
struct TYPE_15__ {int PinId; TYPE_1__ Property; } ;
typedef  TYPE_4__* PKSP_PIN ;
typedef  TYPE_5__* PKSMULTIPLE_ITEM ;
typedef  TYPE_6__* PKSDATAFORMAT_WAVEFORMATEX ;
typedef  TYPE_7__* LPWAVEFORMATEX ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  KSP_PIN ;
typedef  int /*<<< orphan*/  KSMULTIPLE_ITEM ;
typedef  int /*<<< orphan*/  KSDATAFORMAT_WAVEFORMATEX ;
typedef  int /*<<< orphan*/  KSDATAFORMAT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int,...) ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  IOCTL_KS_PROPERTY ; 
 int /*<<< orphan*/  KSDATAFORMAT_SPECIFIER_WAVEFORMATEX ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 int /*<<< orphan*/  KSDATAFORMAT_TYPE_AUDIO ; 
 int /*<<< orphan*/  KSPROPERTY_PIN_DATAINTERSECTION ; 
 int /*<<< orphan*/  KSPROPERTY_TYPE_GET ; 
 int /*<<< orphan*/  KSPROPSETID_Pin ; 
 int SyncOverlappedDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
DoDataIntersection(
    HANDLE hFilter,
    DWORD PinId,
    DWORD SampleFrequency,
    LPWAVEFORMATEX WaveFormatEx,
    DWORD MinimumBitsPerSample,
    DWORD MaximumBitsPerSample,
    DWORD MaximumChannels,
    LPWAVEFORMATEX WaveFormatOut)
{
    DWORD nChannels, nBitsPerSample;
    KSDATAFORMAT_WAVEFORMATEX WaveFormat;
    PKSP_PIN Pin;
    PKSMULTIPLE_ITEM Item;
    PKSDATAFORMAT_WAVEFORMATEX DataFormat;
    DWORD dwResult;

    /* allocate request */
    Pin = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(KSP_PIN) + sizeof(KSMULTIPLE_ITEM) + sizeof(KSDATAFORMAT_WAVEFORMATEX));
    if (!Pin)
    {
        /* no memory */
        return FALSE;
    }

    Item = (PKSMULTIPLE_ITEM)(Pin + 1);
    DataFormat = (PKSDATAFORMAT_WAVEFORMATEX)(Item + 1);

    /* setup request */
    Pin->PinId = PinId;
    Pin->Property.Flags = KSPROPERTY_TYPE_GET;
    Pin->Property.Set = KSPROPSETID_Pin;
    Pin->Property.Id = KSPROPERTY_PIN_DATAINTERSECTION;
    Item->Count = 1;
    Item->Size = sizeof(KSDATAFORMAT_WAVEFORMATEX);


    DataFormat->WaveFormatEx.wFormatTag = WaveFormatEx->wFormatTag;
    DataFormat->WaveFormatEx.nSamplesPerSec = SampleFrequency;
    DataFormat->WaveFormatEx.nBlockAlign = WaveFormatEx->nBlockAlign;
    DataFormat->WaveFormatEx.cbSize = 0;
    DataFormat->DataFormat.FormatSize = sizeof(KSDATAFORMAT) + sizeof(WAVEFORMATEX);
    DataFormat->DataFormat.Flags = 0;
    DataFormat->DataFormat.Reserved = 0;
    DataFormat->DataFormat.MajorFormat = KSDATAFORMAT_TYPE_AUDIO;
    DataFormat->DataFormat.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
    DataFormat->DataFormat.Specifier = KSDATAFORMAT_SPECIFIER_WAVEFORMATEX;
    DataFormat->DataFormat.SampleSize = 4;

    for(nChannels = 1; nChannels <= 2; nChannels++)
    {
        for(nBitsPerSample = MinimumBitsPerSample; nBitsPerSample <= MaximumBitsPerSample; nBitsPerSample += 8)
        {
            DataFormat->WaveFormatEx.nChannels = nChannels;
            DataFormat->WaveFormatEx.nAvgBytesPerSec = (nBitsPerSample / 8) * nChannels * SampleFrequency;
            DataFormat->WaveFormatEx.wBitsPerSample = nBitsPerSample;

            DPRINT("CurrentFormat: InFormat nChannels %u wBitsPerSample %u nSamplesPerSec %u\n",
                   nChannels, nBitsPerSample, SampleFrequency);

            dwResult = SyncOverlappedDeviceIoControl(hFilter, IOCTL_KS_PROPERTY, (LPVOID)Pin, sizeof(KSP_PIN) + sizeof(KSMULTIPLE_ITEM) + sizeof(KSDATAFORMAT_WAVEFORMATEX),
                                                     (LPVOID)&WaveFormat, sizeof(KSDATAFORMAT_WAVEFORMATEX), NULL);

            DPRINT("dwResult %x\n", dwResult);


            if (dwResult == ERROR_SUCCESS)
            {
                /* found a compatible audio range */
                WaveFormatOut->cbSize = 0;
                WaveFormatOut->nBlockAlign = WaveFormatEx->nBlockAlign;
                WaveFormatOut->wFormatTag = WaveFormatEx->wFormatTag;
                WaveFormatOut->nAvgBytesPerSec = (nBitsPerSample / 8) * nChannels * SampleFrequency;
                WaveFormatOut->wBitsPerSample = nBitsPerSample;
                WaveFormatOut->nSamplesPerSec = SampleFrequency;
                WaveFormatOut->nChannels = nChannels;

                /* free buffer */
                HeapFree(GetProcessHeap(), 0, Pin);

                DPRINT("InFormat  nChannels %u wBitsPerSample %u nSamplesPerSec %u\nOutFormat nChannels %u nBitsPerSample %u nSamplesPerSec %u\n",
                       WaveFormatEx->nChannels, WaveFormatEx->wBitsPerSample, WaveFormatEx->nSamplesPerSec,
                       WaveFormatOut->nChannels, WaveFormatOut->wBitsPerSample, WaveFormatOut->nSamplesPerSec);

                return TRUE;
            }
        }
    }

    /* free buffer */
    HeapFree(GetProcessHeap(), 0, Pin);
    ASSERT(0);
    return FALSE;
}