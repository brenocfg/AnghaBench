#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  med ;
struct TYPE_13__ {int /*<<< orphan*/  tymed; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pstg; } ;
struct TYPE_12__ {TYPE_1__ u; int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; } ;
typedef  TYPE_2__ STGMEDIUM ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  ILockBytes ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  TYPE_3__ FORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  CreateILockBytesOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/ * GlobalAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDataObject_GetData (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  IDataObject_GetDataHere (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ILockBytes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_CopyTo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseStgMedium (TYPE_2__*) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StgCreateDocfileOnILockBytes (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TYMED_ISTORAGE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT get_data_from_storage(IDataObject *data, FORMATETC *fmt, HGLOBAL *mem)
{
    HGLOBAL h;
    IStorage *stg;
    HRESULT hr;
    FORMATETC stg_fmt;
    STGMEDIUM med;
    ILockBytes *lbs;

    *mem = NULL;

    h = GlobalAlloc( GMEM_DDESHARE|GMEM_MOVEABLE, 0 );
    if(!h) return E_OUTOFMEMORY;

    hr = CreateILockBytesOnHGlobal(h, FALSE, &lbs);
    if(SUCCEEDED(hr))
    {
        hr = StgCreateDocfileOnILockBytes(lbs, STGM_CREATE|STGM_SHARE_EXCLUSIVE|STGM_READWRITE, 0, &stg);
        ILockBytes_Release(lbs);
    }
    if(FAILED(hr))
    {
        GlobalFree(h);
        return hr;
    }

    stg_fmt = *fmt;
    med.tymed = stg_fmt.tymed = TYMED_ISTORAGE;
    med.u.pstg = stg;
    med.pUnkForRelease = NULL;

    hr = IDataObject_GetDataHere(data, &stg_fmt, &med);
    if(FAILED(hr))
    {
        memset(&med, 0, sizeof(med));
        hr = IDataObject_GetData(data, &stg_fmt, &med);
        if(FAILED(hr)) goto end;

        hr = IStorage_CopyTo(med.u.pstg, 0, NULL, NULL, stg);
        ReleaseStgMedium(&med);
        if(FAILED(hr)) goto end;
    }
    *mem = h;

end:
    IStorage_Release(stg);
    if(FAILED(hr)) GlobalFree(h);
    return hr;
}