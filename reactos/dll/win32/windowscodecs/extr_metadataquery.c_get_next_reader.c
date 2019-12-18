#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  punkVal; int /*<<< orphan*/ * puuid; scalar_t__ uiVal; } ;
struct TYPE_9__ {scalar_t__ vt; TYPE_1__ u; } ;
typedef  TYPE_2__ PROPVARIANT ;
typedef  int /*<<< orphan*/  IWICMetadataReader ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IWICMetadataReader ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IWICMetadataReader_GetValue (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PropVariantClear (TYPE_2__*) ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ VT_CLSID ; 
 scalar_t__ VT_UI2 ; 
 scalar_t__ VT_UNKNOWN ; 
 scalar_t__ WINCODEC_ERR_UNEXPECTEDMETADATATYPE ; 

__attribute__((used)) static HRESULT get_next_reader(IWICMetadataReader *reader, UINT index,
                               GUID *guid, IWICMetadataReader **new_reader)
{
    HRESULT hr;
    PROPVARIANT schema, id, value;

    *new_reader = NULL;

    PropVariantInit(&schema);
    PropVariantInit(&id);
    PropVariantInit(&value);

    if (index)
    {
        schema.vt = VT_UI2;
        schema.u.uiVal = index;
    }

    id.vt = VT_CLSID;
    id.u.puuid = guid;
    hr = IWICMetadataReader_GetValue(reader, &schema, &id, &value);
    if (hr != S_OK) return hr;

    if (value.vt == VT_UNKNOWN)
        hr = IUnknown_QueryInterface(value.u.punkVal, &IID_IWICMetadataReader, (void **)new_reader);
    else
        hr = WINCODEC_ERR_UNEXPECTEDMETADATATYPE;

    PropVariantClear(&value);
    return hr;
}