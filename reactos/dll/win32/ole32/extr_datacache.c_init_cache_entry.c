#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; } ;
struct TYPE_5__ {void* advise_flags; scalar_t__ sink_id; void* save_stream_num; void* load_stream_num; int /*<<< orphan*/  dirty; void* id; TYPE_1__ stgmedium; int /*<<< orphan*/  fmtetc; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FORMATETC ;
typedef  TYPE_2__ DataCacheEntry ;
typedef  void* DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 void* STREAM_NUMBER_NOT_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TYMED_NULL ; 
 int /*<<< orphan*/  copy_formatetc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL init_cache_entry(DataCacheEntry *entry, const FORMATETC *fmt, DWORD advf,
                             DWORD id)
{
    HRESULT hr;

    hr = copy_formatetc(&entry->fmtetc, fmt);
    if (FAILED(hr)) return FALSE;

    entry->stgmedium.tymed = TYMED_NULL;
    entry->stgmedium.pUnkForRelease = NULL;
    entry->id = id;
    entry->dirty = TRUE;
    entry->load_stream_num = STREAM_NUMBER_NOT_SET;
    entry->save_stream_num = STREAM_NUMBER_NOT_SET;
    entry->sink_id = 0;
    entry->advise_flags = advf;

    return TRUE;
}