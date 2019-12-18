#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct addrinfo {scalar_t__ ai_family; int ai_addrlen; struct sockaddr* ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; struct addrinfo* ai_next; int /*<<< orphan*/ * ai_canonname; int /*<<< orphan*/  ai_flags; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  service ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  host ;
struct TYPE_7__ {TYPE_1__* protseq; int /*<<< orphan*/  protseq_entry; } ;
struct TYPE_6__ {int sock; TYPE_4__ common; } ;
struct TYPE_5__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  listeners; int /*<<< orphan*/  MaxCalls; int /*<<< orphan*/  Protseq; } ;
typedef  TYPE_1__ RpcServerProtseq ;
typedef  TYPE_2__ RpcConnection_tcp ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  scalar_t__ RPC_STATUS ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int EAI_NONAME ; 
 int EAI_SERVICE ; 
 int /*<<< orphan*/  ERR (char*,char const*,...) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 scalar_t__ PF_UNSPEC ; 
 scalar_t__ RPCRT4_CreateConnection (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPCRT4_ReleaseConnection (TYPE_4__*) ; 
 scalar_t__ RPC_S_CANT_CREATE_ENDPOINT ; 
 scalar_t__ RPC_S_DUPLICATE_ENDPOINT ; 
 scalar_t__ RPC_S_INVALID_ENDPOINT_FORMAT ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 scalar_t__ WSAEADDRINUSE ; 
 int WSAGetLastError () ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ *,char const*,struct addrinfo*,struct addrinfo**) ; 
 int getnameinfo (struct sockaddr*,int,char*,int,char*,int,int) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS rpcrt4_protseq_ncacn_ip_tcp_open_endpoint(RpcServerProtseq *protseq, const char *endpoint)
{
    RPC_STATUS status = RPC_S_CANT_CREATE_ENDPOINT;
    int sock;
    int ret;
    struct addrinfo *ai;
    struct addrinfo *ai_cur;
    struct addrinfo hints;

    TRACE("(%p, %s)\n", protseq, endpoint);

    hints.ai_flags          = AI_PASSIVE /* for non-localhost addresses */;
    hints.ai_family         = PF_UNSPEC;
    hints.ai_socktype       = SOCK_STREAM;
    hints.ai_protocol       = IPPROTO_TCP;
    hints.ai_addrlen        = 0;
    hints.ai_addr           = NULL;
    hints.ai_canonname      = NULL;
    hints.ai_next           = NULL;

    ret = getaddrinfo(NULL, endpoint ? endpoint : "0", &hints, &ai);
    if (ret)
    {
        ERR("getaddrinfo for port %s failed: %s\n", endpoint,
            gai_strerror(ret));
        if ((ret == EAI_SERVICE) || (ret == EAI_NONAME))
            return RPC_S_INVALID_ENDPOINT_FORMAT;
        return RPC_S_CANT_CREATE_ENDPOINT;
    }

    for (ai_cur = ai; ai_cur; ai_cur = ai_cur->ai_next)
    {
        RpcConnection_tcp *tcpc;
        RPC_STATUS create_status;
        struct sockaddr_storage sa;
        socklen_t sa_len;
        char service[NI_MAXSERV];
        u_long nonblocking;

        if (ai_cur->ai_family != AF_INET && ai_cur->ai_family != AF_INET6)
        {
            TRACE("skipping non-IP/IPv6 address family\n");
            continue;
        }

        if (TRACE_ON(rpc))
        {
            char host[256];
            getnameinfo(ai_cur->ai_addr, ai_cur->ai_addrlen,
                        host, sizeof(host), service, sizeof(service),
                        NI_NUMERICHOST | NI_NUMERICSERV);
            TRACE("trying %s:%s\n", host, service);
        }

        sock = socket(ai_cur->ai_family, ai_cur->ai_socktype, ai_cur->ai_protocol);
        if (sock == -1)
        {
            WARN("socket() failed: %u\n", WSAGetLastError());
            status = RPC_S_CANT_CREATE_ENDPOINT;
            continue;
        }

        ret = bind(sock, ai_cur->ai_addr, ai_cur->ai_addrlen);
        if (ret < 0)
        {
            WARN("bind failed: %u\n", WSAGetLastError());
            closesocket(sock);
            if (WSAGetLastError() == WSAEADDRINUSE)
              status = RPC_S_DUPLICATE_ENDPOINT;
            else
              status = RPC_S_CANT_CREATE_ENDPOINT;
            continue;
        }

        sa_len = sizeof(sa);
        if (getsockname(sock, (struct sockaddr *)&sa, &sa_len))
        {
            WARN("getsockname() failed: %u\n", WSAGetLastError());
            closesocket(sock);
            status = RPC_S_CANT_CREATE_ENDPOINT;
            continue;
        }

        ret = getnameinfo((struct sockaddr *)&sa, sa_len,
                          NULL, 0, service, sizeof(service),
                          NI_NUMERICSERV);
        if (ret)
        {
            WARN("getnameinfo failed: %s\n", gai_strerror(ret));
            closesocket(sock);
            status = RPC_S_CANT_CREATE_ENDPOINT;
            continue;
        }

        create_status = RPCRT4_CreateConnection((RpcConnection **)&tcpc, TRUE,
                                                protseq->Protseq, NULL,
                                                service, NULL, NULL, NULL, NULL);
        if (create_status != RPC_S_OK)
        {
            closesocket(sock);
            status = create_status;
            continue;
        }

        tcpc->sock = sock;
        ret = listen(sock, protseq->MaxCalls);
        if (ret < 0)
        {
            WARN("listen failed: %u\n", WSAGetLastError());
            RPCRT4_ReleaseConnection(&tcpc->common);
            status = RPC_S_OUT_OF_RESOURCES;
            continue;
        }
        /* need a non-blocking socket, otherwise accept() has a potential
         * race-condition (poll() says it is readable, connection drops,
         * and accept() blocks until the next connection comes...)
         */
        nonblocking = 1;
        ret = ioctlsocket(sock, FIONBIO, &nonblocking);
        if (ret < 0)
        {
            WARN("couldn't make socket non-blocking, error %d\n", ret);
            RPCRT4_ReleaseConnection(&tcpc->common);
            status = RPC_S_OUT_OF_RESOURCES;
            continue;
        }

        EnterCriticalSection(&protseq->cs);
        list_add_tail(&protseq->listeners, &tcpc->common.protseq_entry);
        tcpc->common.protseq = protseq;
        LeaveCriticalSection(&protseq->cs);

        freeaddrinfo(ai);

        /* since IPv4 and IPv6 share the same port space, we only need one
         * successful bind to listen for both */
        TRACE("listening on %s\n", endpoint);
        return RPC_S_OK;
    }

    freeaddrinfo(ai);
    ERR("couldn't listen on port %s\n", endpoint);
    return status;
}