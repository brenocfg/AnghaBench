#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pIUnknown; } ;
struct TYPE_7__ {int /*<<< orphan*/  entry; TYPE_1__ interfaces; } ;
typedef  TYPE_2__ Sink ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_E_CANNOTCONNECT ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_Cookie (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_head (struct list*,int /*<<< orphan*/ *) ; 

HRESULT advise_sink(struct list *sink_list, REFIID riid, DWORD cookie_magic, IUnknown *unk, DWORD *cookie)
{
    Sink *sink;

    sink = HeapAlloc(GetProcessHeap(), 0, sizeof(*sink));
    if (!sink)
        return E_OUTOFMEMORY;

    if (FAILED(IUnknown_QueryInterface(unk, riid, (void**)&sink->interfaces.pIUnknown)))
    {
        HeapFree(GetProcessHeap(), 0, sink);
        return CONNECT_E_CANNOTCONNECT;
    }

    list_add_head(sink_list, &sink->entry);
    *cookie = generate_Cookie(cookie_magic, sink);
    TRACE("cookie %x\n", *cookie);
    return S_OK;
}