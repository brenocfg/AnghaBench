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
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  csFilter; } ;
struct TYPE_12__ {double dRate; int /*<<< orphan*/  llStop; } ;
struct TYPE_14__ {TYPE_2__ filter; TYPE_1__ sourceSeeking; TYPE_5__* pInputPin; int /*<<< orphan*/ * ppPins; } ;
struct TYPE_18__ {int position; TYPE_3__ Parser; int /*<<< orphan*/ * header; } ;
struct TYPE_15__ {int tStart; double dRate; int /*<<< orphan*/  IPin_iface; } ;
struct TYPE_11__ {TYPE_4__ pin; } ;
struct TYPE_17__ {TYPE_10__ pin; } ;
struct TYPE_16__ {int rtNext; int rtStop; int rtCurrent; int /*<<< orphan*/  pReader; int /*<<< orphan*/  pAlloc; int /*<<< orphan*/  cbAlign; } ;
typedef  TYPE_5__ PullPin ;
typedef  TYPE_6__ Parser_OutputPin ;
typedef  TYPE_7__ MPEGSplitterImpl ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IMediaSample ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ALIGNUP (int,int /*<<< orphan*/ ) ; 
 int BYTES_FROM_MEDIATIME (int) ; 
 scalar_t__ BaseOutputPinImpl_Deliver (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ IAsyncReader_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAsyncReader_SyncRead (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSample_GetActualDataLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_GetPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IMediaSample_IsDiscontinuity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_SetActualDataLength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IMediaSample_SetDiscontinuity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMediaSample_SetMediaTime (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IMediaSample_SetPreroll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMediaSample_SetSyncPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMediaSample_SetTime (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ IMemAllocator_GetBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IPin_ConnectedTo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IPin_NewSegment (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MEDIATIME_FROM_BYTES (int) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ parse_header (int /*<<< orphan*/ *,int*,int*) ; 
 TYPE_6__* unsafe_impl_Parser_OutputPin_from_IPin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT FillBuffer(MPEGSplitterImpl *This, IMediaSample *pCurrentSample)
{
    Parser_OutputPin * pOutputPin = unsafe_impl_Parser_OutputPin_from_IPin(This->Parser.ppPins[1]);
    LONGLONG length = 0;
    LONGLONG pos = BYTES_FROM_MEDIATIME(This->Parser.pInputPin->rtNext);
    LONGLONG time = This->position, rtstop, rtstart;
    HRESULT hr;
    BYTE *fbuf = NULL;
    DWORD len = IMediaSample_GetActualDataLength(pCurrentSample);

    TRACE("Source length: %u\n", len);
    IMediaSample_GetPointer(pCurrentSample, &fbuf);

    /* Find the next valid header.. it <SHOULD> be right here */
    hr = parse_header(fbuf, &length, &This->position);
    assert(hr == S_OK);
    IMediaSample_SetActualDataLength(pCurrentSample, length);

    /* Queue the next sample */
    if (length + 4 == len)
    {
        PullPin *pin = This->Parser.pInputPin;
        LONGLONG stop = BYTES_FROM_MEDIATIME(pin->rtStop);

        hr = S_OK;
        memcpy(This->header, fbuf + length, 4);
        while (FAILED(hr = parse_header(This->header, &length, NULL)))
        {
            memmove(This->header, This->header+1, 3);
            if (pos + 4 >= stop)
                break;
            IAsyncReader_SyncRead(pin->pReader, ++pos, 1, This->header + 3);
        }
        pin->rtNext = MEDIATIME_FROM_BYTES(pos);

        if (SUCCEEDED(hr))
        {
            /* Remove 4 for the last header, which should hopefully work */
            IMediaSample *sample = NULL;
            LONGLONG rtSampleStart = pin->rtNext - MEDIATIME_FROM_BYTES(4);
            LONGLONG rtSampleStop = rtSampleStart + MEDIATIME_FROM_BYTES(length + 4);

            if (rtSampleStop > pin->rtStop)
                rtSampleStop = MEDIATIME_FROM_BYTES(ALIGNUP(BYTES_FROM_MEDIATIME(pin->rtStop), pin->cbAlign));

            hr = IMemAllocator_GetBuffer(pin->pAlloc, &sample, NULL, NULL, 0);
            if (SUCCEEDED(hr))
            {
                IMediaSample_SetTime(sample, &rtSampleStart, &rtSampleStop);
                IMediaSample_SetPreroll(sample, FALSE);
                IMediaSample_SetDiscontinuity(sample, FALSE);
                IMediaSample_SetSyncPoint(sample, TRUE);
                hr = IAsyncReader_Request(pin->pReader, sample, 0);
                if (SUCCEEDED(hr))
                {
                    pin->rtCurrent = rtSampleStart;
                    pin->rtNext = rtSampleStop;
                }
                else
                    IMediaSample_Release(sample);
            }
            if (FAILED(hr))
                FIXME("o_Ox%08x\n", hr);
        }
    }
    /* If not, we're presumably at the end of file */

    TRACE("Media time : %u.%03u\n", (DWORD)(This->position/10000000), (DWORD)((This->position/10000)%1000));

    if (IMediaSample_IsDiscontinuity(pCurrentSample) == S_OK) {
        IPin *victim;
        EnterCriticalSection(&This->Parser.filter.csFilter);
        pOutputPin->pin.pin.tStart = time;
        pOutputPin->pin.pin.dRate = This->Parser.sourceSeeking.dRate;
        hr = IPin_ConnectedTo(&pOutputPin->pin.pin.IPin_iface, &victim);
        if (hr == S_OK)
        {
            hr = IPin_NewSegment(victim, time, This->Parser.sourceSeeking.llStop,
                                 This->Parser.sourceSeeking.dRate);
            if (hr != S_OK)
                FIXME("NewSegment returns %08x\n", hr);
            IPin_Release(victim);
        }
        LeaveCriticalSection(&This->Parser.filter.csFilter);
        if (hr != S_OK)
            return hr;
    }
    rtstart = (double)(time - pOutputPin->pin.pin.tStart) / pOutputPin->pin.pin.dRate;
    rtstop = (double)(This->position - pOutputPin->pin.pin.tStart) / pOutputPin->pin.pin.dRate;
    IMediaSample_SetTime(pCurrentSample, &rtstart, &rtstop);
    IMediaSample_SetMediaTime(pCurrentSample, &time, &This->position);

    hr = BaseOutputPinImpl_Deliver(&pOutputPin->pin, pCurrentSample);

    if (hr != S_OK)
    {
        if (hr != S_FALSE)
            TRACE("Error sending sample (%x)\n", hr);
        else
            TRACE("S_FALSE (%d), holding\n", IMediaSample_GetActualDataLength(pCurrentSample));
    }

    return hr;
}