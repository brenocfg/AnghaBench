#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* fnFoundSeek ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int nFilters; int /*<<< orphan*/ ** ppFiltersInGraph; } ;
typedef  int /*<<< orphan*/  IMediaSeeking ;
typedef  TYPE_1__ IFilterGraphImpl ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int /*<<< orphan*/  IAMFilterMiscFlags ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ AM_FILTER_MISC_FLAGS_IS_RENDERER ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ IAMFilterMiscFlags_GetMiscFlags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAMFilterMiscFlags_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBaseFilter_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IAMFilterMiscFlags ; 
 int /*<<< orphan*/  IID_IMediaSeeking ; 
 int /*<<< orphan*/  IMediaSeeking_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,scalar_t__ (*) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static HRESULT all_renderers_seek(IFilterGraphImpl *This, fnFoundSeek FoundSeek, DWORD_PTR arg) {
    BOOL allnotimpl = TRUE;
    int i;
    HRESULT hr, hr_return = S_OK;

    TRACE("(%p)->(%p %08lx)\n", This, FoundSeek, arg);
    /* Send a message to all renderers, they are responsible for broadcasting it further */

    for(i = 0; i < This->nFilters; i++)
    {
        IMediaSeeking *seek = NULL;
        IBaseFilter* pfilter = This->ppFiltersInGraph[i];
        IAMFilterMiscFlags *flags = NULL;
        ULONG filterflags;
        IBaseFilter_QueryInterface(pfilter, &IID_IAMFilterMiscFlags, (void**)&flags);
        if (!flags)
            continue;
        filterflags = IAMFilterMiscFlags_GetMiscFlags(flags);
        IAMFilterMiscFlags_Release(flags);
        if (filterflags != AM_FILTER_MISC_FLAGS_IS_RENDERER)
            continue;

        IBaseFilter_QueryInterface(pfilter, &IID_IMediaSeeking, (void**)&seek);
        if (!seek)
            continue;
        hr = FoundSeek(This, seek, arg);
        IMediaSeeking_Release(seek);
        if (hr_return != E_NOTIMPL)
            allnotimpl = FALSE;
        if (hr_return == S_OK || (FAILED(hr) && hr != E_NOTIMPL && SUCCEEDED(hr_return)))
            hr_return = hr;
    }

    if (allnotimpl)
        return E_NOTIMPL;
    return hr_return;
}