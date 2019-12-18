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
struct TYPE_6__ {int /*<<< orphan*/  from; int /*<<< orphan*/  buf; TYPE_2__* link_socket; } ;
struct context {TYPE_3__ c2; } ;
struct TYPE_4__ {scalar_t__ proto; } ;
struct TYPE_5__ {TYPE_1__ info; scalar_t__ socks_proxy; } ;

/* Variables and functions */
 scalar_t__ PROTO_UDP ; 
 int /*<<< orphan*/  socks_process_incoming_udp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
socks_postprocess_incoming_link(struct context *c)
{
    if (c->c2.link_socket->socks_proxy && c->c2.link_socket->info.proto == PROTO_UDP)
    {
        socks_process_incoming_udp(&c->c2.buf, &c->c2.from);
    }
}