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
struct stub_manager {int /*<<< orphan*/  disconnected; int /*<<< orphan*/  oid; } ;
struct ifstub {int /*<<< orphan*/  chan; int /*<<< orphan*/  iface; scalar_t__ stubbuffer; int /*<<< orphan*/  iid; int /*<<< orphan*/  entry; int /*<<< orphan*/  ipid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifstub*) ; 
 int /*<<< orphan*/  IRpcChannelBuffer_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRpcStubBuffer_Release (scalar_t__) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_UnregisterInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct stub_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stub_manager_delete_ifstub(struct stub_manager *m, struct ifstub *ifstub)
{
    TRACE("m=%p, m->oid=%s, ipid=%s\n", m, wine_dbgstr_longlong(m->oid), debugstr_guid(&ifstub->ipid));

    list_remove(&ifstub->entry);

    if (!m->disconnected)
        RPC_UnregisterInterface(&ifstub->iid, TRUE);

    if (ifstub->stubbuffer) IRpcStubBuffer_Release(ifstub->stubbuffer);
    IUnknown_Release(ifstub->iface);
    IRpcChannelBuffer_Release(ifstub->chan);

    HeapFree(GetProcessHeap(), 0, ifstub);
}