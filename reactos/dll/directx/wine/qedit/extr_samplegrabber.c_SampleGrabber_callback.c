#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  csFilter; } ;
struct TYPE_6__ {scalar_t__ bufferLen; int grabberMethod; int /*<<< orphan*/  grabberIface; TYPE_1__ filter; int /*<<< orphan*/ * bufferData; } ;
typedef  TYPE_2__ SG_Impl ;
typedef  int REFERENCE_TIME ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IMediaSample ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * CoTaskMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ IMediaSample_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IMediaSample_GetActualDataLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_GetPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IMediaSample_GetTime (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IMediaSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISampleGrabberCB_BufferCB (int /*<<< orphan*/ ,double,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ISampleGrabberCB_SampleCB (int /*<<< orphan*/ ,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SampleGrabber_callback(SG_Impl *This, IMediaSample *sample)
{
    double time = 0.0;
    REFERENCE_TIME tStart, tEnd;
    if (This->bufferLen >= 0) {
        BYTE *data = 0;
        LONG size = IMediaSample_GetActualDataLength(sample);
        if (size >= 0 && SUCCEEDED(IMediaSample_GetPointer(sample, &data))) {
            if (!data)
                size = 0;
            EnterCriticalSection(&This->filter.csFilter);
            if (This->bufferLen != size) {
                CoTaskMemFree(This->bufferData);
                This->bufferData = size ? CoTaskMemAlloc(size) : NULL;
                This->bufferLen = size;
            }
            if (size)
                CopyMemory(This->bufferData, data, size);
            LeaveCriticalSection(&This->filter.csFilter);
        }
    }
    if (!This->grabberIface)
        return;
    if (SUCCEEDED(IMediaSample_GetTime(sample, &tStart, &tEnd)))
        time = 1e-7 * tStart;
    switch (This->grabberMethod) {
        case 0:
	    {
		ULONG ref = IMediaSample_AddRef(sample);
		ISampleGrabberCB_SampleCB(This->grabberIface, time, sample);
		ref = IMediaSample_Release(sample) + 1 - ref;
		if (ref)
		{
		    ERR("(%p) Callback referenced sample %p by %u\n", This, sample, ref);
		    /* ugly as hell but some apps are sooo buggy */
		    while (ref--)
			IMediaSample_Release(sample);
		}
	    }
            break;
        case 1:
            {
                BYTE *data = 0;
                LONG size = IMediaSample_GetActualDataLength(sample);
                if (size && SUCCEEDED(IMediaSample_GetPointer(sample, &data)) && data)
                    ISampleGrabberCB_BufferCB(This->grabberIface, time, data, size);
            }
            break;
        case -1:
            break;
        default:
            FIXME("unsupported method %d\n", This->grabberMethod);
            /* do not bother us again */
            This->grabberMethod = -1;
    }
}