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
struct regsvr_filter {int /*<<< orphan*/  clsid; int /*<<< orphan*/  category; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IFilterMapper2 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FilterMapper2 ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  IFilterMapper2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFilterMapper2_UnregisterFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IFilterMapper2 ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT unregister_filters(struct regsvr_filter const *list)
{
    HRESULT hr;
    IFilterMapper2* pFM2;

    CoInitialize(NULL);
    
    hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC_SERVER, &IID_IFilterMapper2, (LPVOID*)&pFM2);

    if (SUCCEEDED(hr)) {
	for (; SUCCEEDED(hr) && list->clsid; ++list)
	    hr = IFilterMapper2_UnregisterFilter(pFM2, list->category, NULL, list->clsid);
	IFilterMapper2_Release(pFM2);
    }

    CoUninitialize();
    
    return hr;
}