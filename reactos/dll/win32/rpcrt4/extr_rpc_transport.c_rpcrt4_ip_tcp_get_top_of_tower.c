#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count_lhs; unsigned char protid; int count_rhs; int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ twr_tcp_floor_t ;
struct TYPE_6__ {int count_lhs; int count_rhs; int /*<<< orphan*/  ipv4addr; int /*<<< orphan*/  protid; } ;
typedef  TYPE_3__ twr_ipv4_floor_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/ * ai_canonname; scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  EPM_PROTOCOL_IP ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRACE (char*,unsigned char*,char const*,char const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 

__attribute__((used)) static size_t rpcrt4_ip_tcp_get_top_of_tower(unsigned char *tower_data,
                                             const char *networkaddr,
                                             unsigned char tcp_protid,
                                             const char *endpoint)
{
    twr_tcp_floor_t *tcp_floor;
    twr_ipv4_floor_t *ipv4_floor;
    struct addrinfo *ai;
    struct addrinfo hints;
    int ret;
    size_t size = sizeof(*tcp_floor) + sizeof(*ipv4_floor);

    TRACE("(%p, %s, %s)\n", tower_data, networkaddr, endpoint);

    if (!tower_data)
        return size;

    tcp_floor = (twr_tcp_floor_t *)tower_data;
    tower_data += sizeof(*tcp_floor);

    ipv4_floor = (twr_ipv4_floor_t *)tower_data;

    tcp_floor->count_lhs = sizeof(tcp_floor->protid);
    tcp_floor->protid = tcp_protid;
    tcp_floor->count_rhs = sizeof(tcp_floor->port);

    ipv4_floor->count_lhs = sizeof(ipv4_floor->protid);
    ipv4_floor->protid = EPM_PROTOCOL_IP;
    ipv4_floor->count_rhs = sizeof(ipv4_floor->ipv4addr);

    hints.ai_flags          = AI_NUMERICHOST;
    /* FIXME: only support IPv4 at the moment. how is IPv6 represented by the EPM? */
    hints.ai_family         = PF_INET;
    hints.ai_socktype       = SOCK_STREAM;
    hints.ai_protocol       = IPPROTO_TCP;
    hints.ai_addrlen        = 0;
    hints.ai_addr           = NULL;
    hints.ai_canonname      = NULL;
    hints.ai_next           = NULL;

    ret = getaddrinfo(networkaddr, endpoint, &hints, &ai);
    if (ret)
    {
        ret = getaddrinfo("0.0.0.0", endpoint, &hints, &ai);
        if (ret)
        {
            ERR("getaddrinfo failed: %s\n", gai_strerror(ret));
            return 0;
        }
    }

    if (ai->ai_family == PF_INET)
    {
        const struct sockaddr_in *sin = (const struct sockaddr_in *)ai->ai_addr;
        tcp_floor->port = sin->sin_port;
        ipv4_floor->ipv4addr = sin->sin_addr.s_addr;
    }
    else
    {
        ERR("unexpected protocol family %d\n", ai->ai_family);
        freeaddrinfo(ai);
        return 0;
    }

    freeaddrinfo(ai);

    return size;
}