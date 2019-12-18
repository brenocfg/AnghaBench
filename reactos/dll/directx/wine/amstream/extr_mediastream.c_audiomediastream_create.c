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
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int ref; TYPE_4__ IAMMediaStream_iface; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  purpose_id; int /*<<< orphan*/ * parent; TYPE_2__* input_pin; int /*<<< orphan*/  critical_section; TYPE_1__ IAudioMediaStream_iface; } ;
struct TYPE_13__ {char* achName; int /*<<< orphan*/  dir; int /*<<< orphan*/ * pFilter; } ;
struct TYPE_12__ {TYPE_5__* parent; } ;
typedef  int /*<<< orphan*/  STREAM_TYPE ;
typedef  TYPE_3__ PIN_INFO ;
typedef  int /*<<< orphan*/  MSPID ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IMultiMediaStream ;
typedef  TYPE_4__ IAMMediaStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  AudioMediaStreamInputPin ;
typedef  TYPE_5__ AudioMediaStreamImpl ;

/* Variables and functions */
 int /*<<< orphan*/  AudioMediaStreamImpl_IAMMediaStream_Vtbl ; 
 int /*<<< orphan*/  AudioMediaStreamImpl_IAudioMediaStream_Vtbl ; 
 int /*<<< orphan*/  AudioMediaStreamInputPin_FuncTable ; 
 int /*<<< orphan*/  AudioMediaStreamInputPin_IPin_Vtbl ; 
 int /*<<< orphan*/  BaseInputPin_Construct (int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_PIN_NAME ; 
 int /*<<< orphan*/  PINDIR_INPUT ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/  const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/  const*) ; 

HRESULT audiomediastream_create(IMultiMediaStream *parent, const MSPID *purpose_id,
        STREAM_TYPE stream_type, IAMMediaStream **media_stream)
{
    AudioMediaStreamImpl *object;
    PIN_INFO pin_info;
    HRESULT hr;

    TRACE("(%p,%s,%p)\n", parent, debugstr_guid(purpose_id), media_stream);

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(AudioMediaStreamImpl));
    if (!object)
        return E_OUTOFMEMORY;

    object->IAMMediaStream_iface.lpVtbl = &AudioMediaStreamImpl_IAMMediaStream_Vtbl;
    object->IAudioMediaStream_iface.lpVtbl = &AudioMediaStreamImpl_IAudioMediaStream_Vtbl;
    object->ref = 1;

    InitializeCriticalSection(&object->critical_section);

    pin_info.pFilter = NULL;
    pin_info.dir = PINDIR_INPUT;
    pin_info.achName[0] = 'I';
    StringFromGUID2(purpose_id, pin_info.achName + 1, MAX_PIN_NAME - 1);
    hr = BaseInputPin_Construct(&AudioMediaStreamInputPin_IPin_Vtbl,
        sizeof(AudioMediaStreamInputPin), &pin_info, &AudioMediaStreamInputPin_FuncTable,
        &object->critical_section, NULL, (IPin **)&object->input_pin);
    if (FAILED(hr))
        goto out_object;

    object->input_pin->parent = object;

    object->parent = parent;
    object->purpose_id = *purpose_id;
    object->stream_type = stream_type;

    *media_stream = &object->IAMMediaStream_iface;

    return S_OK;

out_object:
    HeapFree(GetProcessHeap(), 0, object);

    return hr;
}