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
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;
struct TYPE_6__ {TYPE_2__ src; TYPE_1__ dst; } ;
struct vmci_transport_packet {int /*<<< orphan*/  src_port; TYPE_3__ dg; int /*<<< orphan*/  dst_port; } ;
struct sockaddr_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsock_addr_init (struct sockaddr_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vmci_transport_packet_get_addresses(struct vmci_transport_packet *pkt,
				    struct sockaddr_vm *local,
				    struct sockaddr_vm *remote)
{
	vsock_addr_init(local, pkt->dg.dst.context, pkt->dst_port);
	vsock_addr_init(remote, pkt->dg.src.context, pkt->src_port);
}