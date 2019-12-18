#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ proto; int bind_ipv6_only; TYPE_1__* lsa; } ;
struct link_socket {TYPE_2__ info; int /*<<< orphan*/  sd; int /*<<< orphan*/  ctrl_sd; scalar_t__ socks_proxy; scalar_t__ bind_local; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
struct TYPE_3__ {int /*<<< orphan*/  bind_local; } ;

/* Variables and functions */
 scalar_t__ PROTO_UDP ; 
 int /*<<< orphan*/  socket_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,char*,int) ; 

__attribute__((used)) static void
bind_local(struct link_socket *sock, const sa_family_t ai_family)
{
    /* bind to local address/port */
    if (sock->bind_local)
    {
        if (sock->socks_proxy && sock->info.proto == PROTO_UDP)
        {
            socket_bind(sock->ctrl_sd, sock->info.lsa->bind_local,
                        ai_family, "SOCKS", false);
        }
        else
        {
            socket_bind(sock->sd, sock->info.lsa->bind_local,
                        ai_family,
                        "TCP/UDP", sock->info.bind_ipv6_only);
        }
    }
}