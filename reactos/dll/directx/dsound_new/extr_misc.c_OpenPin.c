#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_20__ {int /*<<< orphan*/  wBitsPerSample; int /*<<< orphan*/  nAvgBytesPerSec; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  nChannels; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_17__ {int FormatSize; int SampleSize; int /*<<< orphan*/  Specifier; int /*<<< orphan*/  SubFormat; int /*<<< orphan*/  MajorFormat; scalar_t__ Reserved; scalar_t__ Flags; } ;
struct TYPE_16__ {scalar_t__ cbSize; int /*<<< orphan*/  wBitsPerSample; int /*<<< orphan*/  nAvgBytesPerSec; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  nChannels; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_19__ {TYPE_5__ DataFormat; TYPE_4__ WaveFormatEx; } ;
struct TYPE_15__ {int PrioritySubClass; int /*<<< orphan*/  PriorityClass; } ;
struct TYPE_14__ {scalar_t__ Flags; int /*<<< orphan*/  Id; int /*<<< orphan*/  Set; } ;
struct TYPE_13__ {scalar_t__ Flags; int /*<<< orphan*/  Id; int /*<<< orphan*/  Set; } ;
struct TYPE_18__ {TYPE_3__ Priority; int /*<<< orphan*/  PinId; int /*<<< orphan*/ * PinToHandle; TYPE_2__ Medium; TYPE_1__ Interface; } ;
typedef  TYPE_6__* PKSPIN_CONNECT ;
typedef  TYPE_7__* PKSDATAFORMAT_WAVEFORMATEX ;
typedef  int /*<<< orphan*/  PHANDLE ;
typedef  TYPE_8__* LPWAVEFORMATEX ;
typedef  int /*<<< orphan*/  KSPIN_CONNECT ;
typedef  int /*<<< orphan*/  KSDATAFORMAT_WAVEFORMATEX ;
typedef  int /*<<< orphan*/  KSDATAFORMAT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DSERR_OUTOFMEMORY ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_6__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SPECIFIER_WAVEFORMATEX ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 int /*<<< orphan*/  KSDATAFORMAT_TYPE_AUDIO ; 
 int /*<<< orphan*/  KSINTERFACESETID_Standard ; 
 int /*<<< orphan*/  KSINTERFACE_STANDARD_LOOPED_STREAMING ; 
 int /*<<< orphan*/  KSINTERFACE_STANDARD_STREAMING ; 
 int /*<<< orphan*/  KSMEDIUMSETID_Standard ; 
 int /*<<< orphan*/  KSMEDIUM_TYPE_ANYINSTANCE ; 
 int /*<<< orphan*/  KSPRIORITY_NORMAL ; 
 int KsCreatePin (int /*<<< orphan*/ ,TYPE_6__*,int,int /*<<< orphan*/ ) ; 

DWORD
OpenPin(
    HANDLE hFilter,
    ULONG PinId,
    LPWAVEFORMATEX WaveFormatEx,
    PHANDLE hPin,
    BOOL bLoop)
{
    DWORD Size, Result;
    PKSPIN_CONNECT PinConnect;
    PKSDATAFORMAT_WAVEFORMATEX DataFormat;

    /* calculate request size */
    Size = sizeof(KSPIN_CONNECT) + sizeof(KSDATAFORMAT_WAVEFORMATEX);

    PinConnect = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
    if (!PinConnect)
    {
        /* not enough memory */
        return DSERR_OUTOFMEMORY;
    }
    /* build pin request */
    PinConnect->Interface.Set = KSINTERFACESETID_Standard;

    if (bLoop)
        PinConnect->Interface.Id = KSINTERFACE_STANDARD_LOOPED_STREAMING;
    else
        PinConnect->Interface.Id = KSINTERFACE_STANDARD_STREAMING;

    PinConnect->Interface.Flags = 0;
    PinConnect->Medium.Set = KSMEDIUMSETID_Standard;
    PinConnect->Medium.Id = KSMEDIUM_TYPE_ANYINSTANCE;
    PinConnect->Medium.Flags = 0;
    PinConnect->PinToHandle = NULL;
    PinConnect->PinId = PinId;
    PinConnect->Priority.PriorityClass = KSPRIORITY_NORMAL;
    PinConnect->Priority.PrioritySubClass = 1;

    DataFormat = (PKSDATAFORMAT_WAVEFORMATEX) (PinConnect + 1);

    /* initialize data format */
    DataFormat->WaveFormatEx.wFormatTag = WaveFormatEx->wFormatTag;
    DataFormat->WaveFormatEx.nChannels = WaveFormatEx->nChannels;
    DataFormat->WaveFormatEx.nSamplesPerSec = WaveFormatEx->nSamplesPerSec;
    DataFormat->WaveFormatEx.nBlockAlign = WaveFormatEx->nBlockAlign;
    DataFormat->WaveFormatEx.nAvgBytesPerSec = WaveFormatEx->nAvgBytesPerSec;
    DataFormat->WaveFormatEx.wBitsPerSample = WaveFormatEx->wBitsPerSample;
    DataFormat->WaveFormatEx.cbSize = 0;
    DataFormat->DataFormat.FormatSize = sizeof(KSDATAFORMAT) + sizeof(WAVEFORMATEX);
    DataFormat->DataFormat.Flags = 0;
    DataFormat->DataFormat.Reserved = 0;
    DataFormat->DataFormat.MajorFormat = KSDATAFORMAT_TYPE_AUDIO;

    DataFormat->DataFormat.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
    DataFormat->DataFormat.Specifier = KSDATAFORMAT_SPECIFIER_WAVEFORMATEX;
    DataFormat->DataFormat.SampleSize = 4;

    Result = KsCreatePin(hFilter, PinConnect, GENERIC_READ | GENERIC_WRITE, hPin);

    HeapFree(GetProcessHeap(), 0, PinConnect);

    return Result;
}