#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  med ;
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
struct TYPE_16__ {int /*<<< orphan*/  tymed; } ;
struct TYPE_15__ {scalar_t__ QuadPart; } ;
struct TYPE_13__ {int /*<<< orphan*/ * pstm; } ;
struct TYPE_14__ {TYPE_1__ u; int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  TYPE_4__ FORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/ * GlobalAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDataObject_GetData (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  IDataObject_GetDataHere (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  IStream_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 int /*<<< orphan*/  STREAM_SEEK_CUR ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TYMED_ISTREAM ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT get_data_from_stream(IDataObject *data, FORMATETC *fmt, HGLOBAL *mem)
{
    HGLOBAL h;
    IStream *stm = NULL;
    HRESULT hr;
    FORMATETC stm_fmt;
    STGMEDIUM med;

    *mem = NULL;

    h = GlobalAlloc( GMEM_DDESHARE|GMEM_MOVEABLE, 0 );
    if(!h) return E_OUTOFMEMORY;

    hr = CreateStreamOnHGlobal(h, FALSE, &stm);
    if(FAILED(hr)) goto error;

    stm_fmt = *fmt;
    med.tymed = stm_fmt.tymed = TYMED_ISTREAM;
    med.u.pstm = stm;
    med.pUnkForRelease = NULL;

    hr = IDataObject_GetDataHere(data, &stm_fmt, &med);
    if(FAILED(hr))
    {
        LARGE_INTEGER offs;
        ULARGE_INTEGER pos;

        memset(&med, 0, sizeof(med));
        hr = IDataObject_GetData(data, &stm_fmt, &med);
        if(FAILED(hr)) goto error;

        offs.QuadPart = 0;
        IStream_Seek(med.u.pstm, offs, STREAM_SEEK_CUR, &pos);
        IStream_Seek(med.u.pstm, offs, STREAM_SEEK_SET, NULL);
        hr = IStream_CopyTo(med.u.pstm, stm, pos, NULL, NULL);
        ReleaseStgMedium(&med);
        if(FAILED(hr)) goto error;
    }
    *mem = h;
    IStream_Release(stm);
    return S_OK;

error:
    if(stm) IStream_Release(stm);
    GlobalFree(h);
    return hr;
}