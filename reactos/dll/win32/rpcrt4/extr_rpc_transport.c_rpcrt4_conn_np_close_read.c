#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  io_status; int /*<<< orphan*/  pipe; int /*<<< orphan*/  read_closed; } ;
typedef  TYPE_1__ RpcConnection_np ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  NtCancelIoFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtCancelIoFileEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void rpcrt4_conn_np_close_read(RpcConnection *conn)
{
    RpcConnection_np *connection = (RpcConnection_np*)conn;
    IO_STATUS_BLOCK io_status;

    connection->read_closed = TRUE;
#ifdef __REACTOS__ /* FIXME: We should also cancel I/O for other threads */
    NtCancelIoFile(connection->pipe, &io_status);
#else
    NtCancelIoFileEx(connection->pipe, &connection->io_status, &io_status);
#endif
}