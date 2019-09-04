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
typedef  int /*<<< orphan*/  u8_t ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
typedef  int sockaddr ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;
struct TYPE_3__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ lwIP_sock ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  MEMCPY (int*,struct sockaddr_in*,int) ; 
 TYPE_1__* get_socket (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr_from_ipaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwIP_ASSERT (int*) ; 
 int /*<<< orphan*/  netconn_getaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lwip_getaddrname(int s, struct sockaddr *name, socklen_t *namelen, u8_t local)
{
    lwIP_sock *sock = NULL;
    struct sockaddr_in sin;
    ip_addr_t naddr;
    lwIP_ASSERT(name);
    lwIP_ASSERT(namelen);

    sock = get_socket(s);
    if (!sock)
    {
        return -1;
    }

    os_memset(&sin, 0, sizeof(sin));
    sin.sin_len = sizeof(sin);
    sin.sin_family = AF_INET;

    /* get the IP address and port */
    netconn_getaddr(sock->conn, &naddr, &sin.sin_port, local);
    sin.sin_port = htons(sin.sin_port);
    inet_addr_from_ipaddr(&sin.sin_addr, &naddr);

    if (*namelen > sizeof(sin))
    {
        *namelen = sizeof(sin);
    }

    MEMCPY(name, &sin, *namelen);

    return 0;
}