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
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void*,unsigned int,int) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ WSAEINTR ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int recv (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrt4_sock_wait_for_recv (TYPE_1__*) ; 

__attribute__((used)) static int rpcrt4_conn_tcp_read(RpcConnection *Connection,
                                void *buffer, unsigned int count)
{
  RpcConnection_tcp *tcpc = (RpcConnection_tcp *) Connection;
  int bytes_read = 0;
  while (bytes_read != count)
  {
    int r = recv(tcpc->sock, (char *)buffer + bytes_read, count - bytes_read, 0);
    if (!r)
      return -1;
    else if (r > 0)
      bytes_read += r;
    else if (WSAGetLastError() == WSAEINTR)
      continue;
    else if (WSAGetLastError() != WSAEWOULDBLOCK)
    {
      WARN("recv() failed: %u\n", WSAGetLastError());
      return -1;
    }
    else
    {
      if (!rpcrt4_sock_wait_for_recv(tcpc))
        return -1;
    }
  }
  TRACE("%d %p %u -> %d\n", tcpc->sock, buffer, count, bytes_read);
  return bytes_read;
}