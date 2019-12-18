#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  listen_event; scalar_t__ pipe; } ;
typedef  TYPE_1__ RpcConnection_np ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void rpcrt4_conn_np_handoff(RpcConnection_np *old_npc, RpcConnection_np *new_npc)
{    
    /* because of the way named pipes work, we'll transfer the connected pipe
     * to the child, then reopen the server binding to continue listening */

    new_npc->pipe = old_npc->pipe;
    old_npc->pipe = 0;
    assert(!old_npc->listen_event);
}