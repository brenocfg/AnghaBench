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
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_15__ {int /*<<< orphan*/  csFilter; } ;
struct TYPE_14__ {double dRate; int /*<<< orphan*/  llStop; } ;
struct TYPE_16__ {TYPE_3__ filter; TYPE_2__ sourceSeeking; int /*<<< orphan*/ * ppPins; } ;
struct TYPE_20__ {TYPE_4__ Parser; TYPE_6__* streams; } ;
struct TYPE_17__ {int tStart; double dRate; int /*<<< orphan*/  IPin_iface; } ;
struct TYPE_12__ {TYPE_5__ pin; } ;
struct TYPE_19__ {int dwSamplesProcessed; TYPE_10__ pin; } ;
struct TYPE_13__ {int dwScale; int dwRate; int dwSampleSize; } ;
struct TYPE_18__ {TYPE_1__ streamheader; } ;
typedef  TYPE_6__ StreamData ;
typedef  TYPE_7__ Parser_OutputPin ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IMediaSample ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  TYPE_8__ AVISplitterImpl ;

/* Variables and functions */
 scalar_t__ BaseOutputPinImpl_Deliver (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int IMediaSample_GetActualDataLength (int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSample_IsDiscontinuity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_SetMediaTime (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IMediaSample_SetTime (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ IPin_ConnectedTo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IPin_NewSegment (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 TYPE_7__* unsafe_impl_Parser_OutputPin_from_IPin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT AVISplitter_Receive(AVISplitterImpl *This, IMediaSample *sample, DWORD streamnumber)
{
    Parser_OutputPin *pin = unsafe_impl_Parser_OutputPin_from_IPin(This->Parser.ppPins[1+streamnumber]);
    HRESULT hr;
    LONGLONG start, stop, rtstart, rtstop;
    StreamData *stream = &This->streams[streamnumber];

    start = pin->dwSamplesProcessed;
    start *= stream->streamheader.dwScale;
    start *= 10000000;
    start /= stream->streamheader.dwRate;

    if (stream->streamheader.dwSampleSize)
    {
        ULONG len = IMediaSample_GetActualDataLength(sample);
        ULONG size = stream->streamheader.dwSampleSize;

        pin->dwSamplesProcessed += len / size;
    }
    else
        ++pin->dwSamplesProcessed;

    stop = pin->dwSamplesProcessed;
    stop *= stream->streamheader.dwScale;
    stop *= 10000000;
    stop /= stream->streamheader.dwRate;

    if (IMediaSample_IsDiscontinuity(sample) == S_OK) {
        IPin *victim;
        EnterCriticalSection(&This->Parser.filter.csFilter);
        pin->pin.pin.tStart = start;
        pin->pin.pin.dRate = This->Parser.sourceSeeking.dRate;
        hr = IPin_ConnectedTo(&pin->pin.pin.IPin_iface, &victim);
        if (hr == S_OK)
        {
            hr = IPin_NewSegment(victim, start, This->Parser.sourceSeeking.llStop,
                                 This->Parser.sourceSeeking.dRate);
            if (hr != S_OK)
                FIXME("NewSegment returns %08x\n", hr);
            IPin_Release(victim);
        }
        LeaveCriticalSection(&This->Parser.filter.csFilter);
        if (hr != S_OK)
            return hr;
    }
    rtstart = (double)(start - pin->pin.pin.tStart) / pin->pin.pin.dRate;
    rtstop = (double)(stop - pin->pin.pin.tStart) / pin->pin.pin.dRate;
    IMediaSample_SetMediaTime(sample, &start, &stop);
    IMediaSample_SetTime(sample, &rtstart, &rtstop);
    IMediaSample_SetMediaTime(sample, &start, &stop);

    hr = BaseOutputPinImpl_Deliver(&pin->pin, sample);

/* Uncomment this if you want to debug the time differences between the
 * different streams, it is useful for that
 *
    FIXME("stream %u, hr: %08x, Start: %u.%03u, Stop: %u.%03u\n", streamnumber, hr,
           (DWORD)(start / 10000000), (DWORD)((start / 10000)%1000),
           (DWORD)(stop / 10000000), (DWORD)((stop / 10000)%1000));
*/
    return hr;
}