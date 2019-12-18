#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cfFormat; } ;
struct TYPE_8__ {TYPE_1__ fmtetc; int /*<<< orphan*/  load_stream_num; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DataCacheEntry ;

/* Variables and functions */
#define  CF_DIB 130 
#define  CF_ENHMETAFILE 129 
#define  CF_METAFILEPICT 128 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OLE_E_BLANK ; 
 int /*<<< orphan*/  load_dib (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_emf (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_mf_pict (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_pres_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT DataCacheEntry_LoadData(DataCacheEntry *cache_entry, IStorage *stg)
{
    HRESULT hr;
    IStream *stm;

    if (!stg) return OLE_E_BLANK;
    hr = open_pres_stream( stg, cache_entry->load_stream_num, &stm );
    if (FAILED(hr)) return hr;

    switch (cache_entry->fmtetc.cfFormat)
    {
    case CF_METAFILEPICT:
        hr = load_mf_pict( cache_entry, stm );
        break;

    case CF_DIB:
        hr = load_dib( cache_entry, stm );
        break;

    case CF_ENHMETAFILE:
        hr = load_emf( cache_entry, stm );
        break;

    default:
        FIXME( "Unimplemented clip format %x\n", cache_entry->fmtetc.cfFormat );
        hr = E_NOTIMPL;
    }

    IStream_Release( stm );
    return hr;
}