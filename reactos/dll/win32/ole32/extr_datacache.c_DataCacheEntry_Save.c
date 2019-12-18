#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cfFormat; } ;
struct TYPE_9__ {int id; TYPE_6__ fmtetc; int /*<<< orphan*/  save_stream_num; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DataCacheEntry ;
typedef  int BOOL ;

/* Variables and functions */
#define  CF_DIB 130 
#define  CF_ENHMETAFILE 129 
#define  CF_METAFILEPICT 128 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_stream (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_formatetc (TYPE_6__*) ; 
 int /*<<< orphan*/  save_dib (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_emf (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_mfpict (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_view_cache (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT DataCacheEntry_Save(DataCacheEntry *cache_entry, IStorage *storage,
                                   BOOL same_as_load)
{
    HRESULT hr;
    IStream *stream;
    BOOL contents = (cache_entry->id == 1);

    TRACE("stream_number = %d, fmtetc = %s\n", cache_entry->save_stream_num, debugstr_formatetc(&cache_entry->fmtetc));

    hr = create_stream(cache_entry, storage, contents, &stream);
    if (FAILED(hr))
        return hr;

    switch (cache_entry->fmtetc.cfFormat)
    {
    case CF_DIB:
        hr = save_dib(cache_entry, contents, stream);
        break;
    case CF_METAFILEPICT:
        hr = save_mfpict(cache_entry, contents, stream);
        break;
    case CF_ENHMETAFILE:
        hr = save_emf(cache_entry, contents, stream);
        break;
    case 0:
        hr = save_view_cache(cache_entry, stream);
        break;
    default:
        FIXME("got unsupported clipboard format %x\n", cache_entry->fmtetc.cfFormat);
    }

    IStream_Release(stream);
    return hr;
}