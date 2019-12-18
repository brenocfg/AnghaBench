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
struct link_socket_actual {int dummy; } ;
struct TYPE_6__ {TYPE_2__* link_socket; int /*<<< orphan*/  to_link_addr; int /*<<< orphan*/  to_link; } ;
struct context {TYPE_3__ c2; } ;
struct TYPE_4__ {scalar_t__ proto; } ;
struct TYPE_5__ {struct link_socket_actual socks_relay; TYPE_1__ info; scalar_t__ socks_proxy; } ;

/* Variables and functions */
 scalar_t__ PROTO_UDP ; 
 scalar_t__ socks_process_outgoing_udp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
socks_preprocess_outgoing_link(struct context *c,
                               struct link_socket_actual **to_addr,
                               int *size_delta)
{
    if (c->c2.link_socket->socks_proxy && c->c2.link_socket->info.proto == PROTO_UDP)
    {
        *size_delta += socks_process_outgoing_udp(&c->c2.to_link, c->c2.to_link_addr);
        *to_addr = &c->c2.link_socket->socks_relay;
    }
}