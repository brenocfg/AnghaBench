#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * LPSTREAM ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ E_PENDING ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IStream ; 
 scalar_t__ IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ RegisterBindStatusCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static HRESULT URLStartDownload(LPCWSTR szURL, LPSTREAM *ppStream, IBindStatusCallback *pBSC)
{
    HRESULT hr;
    IMoniker *pMoniker;
    IBindCtx *pbc;

    *ppStream = NULL;

    hr = CreateURLMoniker(NULL, szURL, &pMoniker);
    if (FAILED(hr))
        return hr;

    hr = CreateBindCtx(0, &pbc);
    if (FAILED(hr))
    {
        IMoniker_Release(pMoniker);
        return hr;
    }

    hr = RegisterBindStatusCallback(pbc, pBSC, NULL, 0);
    if (FAILED(hr))
    {
        IBindCtx_Release(pbc);
        IMoniker_Release(pMoniker);
        return hr;
    }

    hr = IMoniker_BindToStorage(pMoniker, pbc, NULL, &IID_IStream, (void **)ppStream);

    /* BindToStorage returning E_PENDING because it's asynchronous is not an error */
    if (hr == E_PENDING) hr = S_OK;

    IBindCtx_Release(pbc);
    IMoniker_Release(pMoniker);

    return hr;
}