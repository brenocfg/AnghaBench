#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ Status; } ;
struct TYPE_9__ {unsigned int Information; TYPE_1__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  pipe; } ;
typedef  TYPE_2__ RpcConnection_np ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_3__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ NtWriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,void const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_PENDING ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_np_event (TYPE_2__*) ; 
 int /*<<< orphan*/  release_np_event (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpcrt4_conn_np_write(RpcConnection *conn, const void *buffer, unsigned int count)
{
    RpcConnection_np *connection = (RpcConnection_np *) conn;
    IO_STATUS_BLOCK io_status;
    HANDLE event;
    NTSTATUS status;

    event = get_np_event(connection);
    if (!event)
        return -1;

    status = NtWriteFile(connection->pipe, event, NULL, NULL, &io_status, buffer, count, NULL, NULL);
    if (status == STATUS_PENDING)
    {
        WaitForSingleObject(event, INFINITE);
        status = io_status.u.Status;
    }
    release_np_event(connection, event);
    if (status)
        return -1;

    assert(io_status.Information == count);
    return count;
}