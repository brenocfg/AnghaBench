#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  hEnhMetaFile; } ;
struct TYPE_20__ {scalar_t__ tymed; TYPE_2__ u; } ;
struct TYPE_18__ {int /*<<< orphan*/  cfFormat; } ;
struct TYPE_23__ {TYPE_3__ stgmedium; TYPE_1__ fmtetc; } ;
struct TYPE_22__ {int /*<<< orphan*/  yExt; int /*<<< orphan*/  xExt; } ;
struct TYPE_21__ {int dwSize; int /*<<< orphan*/  dwObjectExtentY; int /*<<< orphan*/  dwObjectExtentX; } ;
typedef  TYPE_4__ PresentationDataHeader ;
typedef  TYPE_5__ METAFILEPICT ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  ENHMETAHEADER ;
typedef  TYPE_6__ DataCacheEntry ;
typedef  int DWORD ;
typedef  TYPE_4__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetEnhMetaFileBits (int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetWinMetaFileBits (int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ IStream_Write (int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MM_ANISOTROPIC ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TYMED_NULL ; 
 int /*<<< orphan*/  init_stream_header (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 scalar_t__ write_clipformat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT save_emf(DataCacheEntry *entry, BOOL contents, IStream *stream)
{
    HRESULT hr = S_OK;
    int data_size = 0;
    BYTE *data;

    if (!contents)
    {
        PresentationDataHeader header;
        METAFILEPICT *mfpict;
        HDC hdc = GetDC(0);

        init_stream_header(entry, &header);
        hr = write_clipformat(stream, entry->fmtetc.cfFormat);
        if (FAILED(hr))
        {
            ReleaseDC(0, hdc);
            return hr;
        }
        data_size = GetWinMetaFileBits(entry->stgmedium.u.hEnhMetaFile, 0, NULL, MM_ANISOTROPIC, hdc);
        header.dwSize = data_size;
        data = HeapAlloc(GetProcessHeap(), 0, header.dwSize);
        if (!data)
        {
            ReleaseDC(0, hdc);
            return E_OUTOFMEMORY;
        }
        GetWinMetaFileBits(entry->stgmedium.u.hEnhMetaFile, header.dwSize, data, MM_ANISOTROPIC, hdc);
        ReleaseDC(0, hdc);
        mfpict = (METAFILEPICT *)data;
        header.dwObjectExtentX = mfpict->xExt;
        header.dwObjectExtentY = mfpict->yExt;
        hr = IStream_Write(stream, &header, sizeof(PresentationDataHeader), NULL);
        if (hr == S_OK && data_size)
            hr = IStream_Write(stream, data, data_size, NULL);
        HeapFree(GetProcessHeap(), 0, data);
    }
    else if (entry->stgmedium.tymed != TYMED_NULL)
    {
        data_size = GetEnhMetaFileBits(entry->stgmedium.u.hEnhMetaFile, 0, NULL);
        data = HeapAlloc(GetProcessHeap(), 0, sizeof(DWORD) + sizeof(ENHMETAHEADER) + data_size);
        if (!data) return E_OUTOFMEMORY;
        *((DWORD *)data) = sizeof(ENHMETAHEADER);
        GetEnhMetaFileBits(entry->stgmedium.u.hEnhMetaFile, data_size, data + sizeof(DWORD) + sizeof(ENHMETAHEADER));
        memcpy(data + sizeof(DWORD), data + sizeof(DWORD) + sizeof(ENHMETAHEADER), sizeof(ENHMETAHEADER));
        data_size += sizeof(DWORD) + sizeof(ENHMETAHEADER);
        hr = IStream_Write(stream, data, data_size, NULL);
        HeapFree(GetProcessHeap(), 0, data);
    }

    return hr;
}