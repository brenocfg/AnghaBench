#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ travellog_entry_t ;
struct TYPE_9__ {unsigned int loading_pos; TYPE_2__* log; } ;
struct TYPE_12__ {int /*<<< orphan*/  document; TYPE_1__ travellog; int /*<<< orphan*/  doc_navigate; } ;
struct TYPE_11__ {scalar_t__ QuadPart; } ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IPersistHistory ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IID_IPersistHistory ; 
 int /*<<< orphan*/  IPersistHistory_LoadHistory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistHistory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  async_doc_navigate (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_navigation_commands (TYPE_4__*) ; 

__attribute__((used)) static HRESULT navigate_history(DocHost *This, unsigned travellog_pos)
{
    IPersistHistory *persist_history;
    travellog_entry_t *entry;
    LARGE_INTEGER li;
    HRESULT hres;

    if(!This->doc_navigate) {
        FIXME("unsupported doc_navigate FALSE\n");
        return E_NOTIMPL;
    }

    This->travellog.loading_pos = travellog_pos;
    entry = This->travellog.log + This->travellog.loading_pos;

    update_navigation_commands(This);

    if(!entry->stream)
        return async_doc_navigate(This, entry->url, NULL, NULL, 0, FALSE);

    hres = IUnknown_QueryInterface(This->document, &IID_IPersistHistory, (void**)&persist_history);
    if(FAILED(hres))
        return hres;

    li.QuadPart = 0;
    IStream_Seek(entry->stream, li, STREAM_SEEK_SET, NULL);

    hres = IPersistHistory_LoadHistory(persist_history, entry->stream, NULL);
    IPersistHistory_Release(persist_history);
    return hres;
}