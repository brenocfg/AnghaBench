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
typedef  int /*<<< orphan*/  RpcConnection_tcp ;
typedef  int /*<<< orphan*/  RpcConnection ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrt4_sock_wait_for_recv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpcrt4_conn_tcp_wait_for_incoming_data(RpcConnection *Connection)
{
    RpcConnection_tcp *tcpc = (RpcConnection_tcp *) Connection;

    TRACE("%p\n", Connection);

    if (!rpcrt4_sock_wait_for_recv(tcpc))
        return -1;
    return 0;
}