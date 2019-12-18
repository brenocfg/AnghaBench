#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
typedef  int u_long ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addrlen; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; struct addrinfo* ai_next; int /*<<< orphan*/ * ai_canonname; scalar_t__ ai_flags; } ;
typedef  int /*<<< orphan*/  service ;
typedef  int /*<<< orphan*/  host ;
struct TYPE_5__ {int /*<<< orphan*/  Endpoint; int /*<<< orphan*/  NetworkAddr; } ;
struct TYPE_4__ {int sock; } ;
typedef  TYPE_1__ RpcConnection_tcp ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 scalar_t__ PF_UNSPEC ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_SERVER_UNAVAILABLE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  getnameinfo (int /*<<< orphan*/ *,scalar_t__,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rpc ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS rpcrt4_ncacn_ip_tcp_open(RpcConnection* Connection)
{
  RpcConnection_tcp *tcpc = (RpcConnection_tcp *) Connection;
  int sock;
  int ret;
  struct addrinfo *ai;
  struct addrinfo *ai_cur;
  struct addrinfo hints;

  TRACE("(%s, %s)\n", Connection->NetworkAddr, Connection->Endpoint);

  if (tcpc->sock != -1)
    return RPC_S_OK;

  hints.ai_flags          = 0;
  hints.ai_family         = PF_UNSPEC;
  hints.ai_socktype       = SOCK_STREAM;
  hints.ai_protocol       = IPPROTO_TCP;
  hints.ai_addrlen        = 0;
  hints.ai_addr           = NULL;
  hints.ai_canonname      = NULL;
  hints.ai_next           = NULL;

  ret = getaddrinfo(Connection->NetworkAddr, Connection->Endpoint, &hints, &ai);
  if (ret)
  {
    ERR("getaddrinfo for %s:%s failed: %s\n", Connection->NetworkAddr,
      Connection->Endpoint, gai_strerror(ret));
    return RPC_S_SERVER_UNAVAILABLE;
  }

  for (ai_cur = ai; ai_cur; ai_cur = ai_cur->ai_next)
  {
    int val;
    u_long nonblocking;

    if (ai_cur->ai_family != AF_INET && ai_cur->ai_family != AF_INET6)
    {
      TRACE("skipping non-IP/IPv6 address family\n");
      continue;
    }

    if (TRACE_ON(rpc))
    {
      char host[256];
      char service[256];
      getnameinfo(ai_cur->ai_addr, ai_cur->ai_addrlen,
        host, sizeof(host), service, sizeof(service),
        NI_NUMERICHOST | NI_NUMERICSERV);
      TRACE("trying %s:%s\n", host, service);
    }

    sock = socket(ai_cur->ai_family, ai_cur->ai_socktype, ai_cur->ai_protocol);
    if (sock == -1)
    {
      WARN("socket() failed: %u\n", WSAGetLastError());
      continue;
    }

    if (0>connect(sock, ai_cur->ai_addr, ai_cur->ai_addrlen))
    {
      WARN("connect() failed: %u\n", WSAGetLastError());
      closesocket(sock);
      continue;
    }

    /* RPC depends on having minimal latency so disable the Nagle algorithm */
    val = 1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&val, sizeof(val));
    nonblocking = 1;
    ioctlsocket(sock, FIONBIO, &nonblocking);

    tcpc->sock = sock;

    freeaddrinfo(ai);
    TRACE("connected\n");
    return RPC_S_OK;
  }

  freeaddrinfo(ai);
  ERR("couldn't connect to %s:%s\n", Connection->NetworkAddr, Connection->Endpoint);
  return RPC_S_SERVER_UNAVAILABLE;
}