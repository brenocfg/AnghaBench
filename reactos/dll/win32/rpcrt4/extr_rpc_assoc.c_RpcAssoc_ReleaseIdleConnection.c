#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  free_connection_pool; scalar_t__ assoc_group_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  conn_pool_entry; scalar_t__ assoc_group_id; int /*<<< orphan*/ * async_state; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ RpcConnection ;
typedef  TYPE_2__ RpcAssoc ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void RpcAssoc_ReleaseIdleConnection(RpcAssoc *assoc, RpcConnection *Connection)
{
    assert(!Connection->server);
    Connection->async_state = NULL;
    EnterCriticalSection(&assoc->cs);
    if (!assoc->assoc_group_id) assoc->assoc_group_id = Connection->assoc_group_id;
    list_add_head(&assoc->free_connection_pool, &Connection->conn_pool_entry);
    LeaveCriticalSection(&assoc->cs);
}