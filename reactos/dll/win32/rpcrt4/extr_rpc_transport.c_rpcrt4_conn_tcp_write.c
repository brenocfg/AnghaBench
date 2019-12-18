#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ RpcConnection_tcp ;
typedef  int /*<<< orphan*/  RpcConnection ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void const*,unsigned int,int) ; 
 scalar_t__ WSAEINTR ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  rpcrt4_sock_wait_for_send (TYPE_1__*) ; 
 int send (int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpcrt4_conn_tcp_write(RpcConnection *Connection,
                                 const void *buffer, unsigned int count)
{
  RpcConnection_tcp *tcpc = (RpcConnection_tcp *) Connection;
  int bytes_written = 0;
  while (bytes_written != count)
  {
    int r = send(tcpc->sock, (const char *)buffer + bytes_written, count - bytes_written, 0);
    if (r >= 0)
      bytes_written += r;
    else if (WSAGetLastError() == WSAEINTR)
      continue;
    else if (WSAGetLastError() != WSAEWOULDBLOCK)
      return -1;
    else
    {
      if (!rpcrt4_sock_wait_for_send(tcpc))
        return -1;
    }
  }
  TRACE("%d %p %u -> %d\n", tcpc->sock, buffer, count, bytes_written);
  return bytes_written;
}