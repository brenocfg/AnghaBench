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
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; int /*<<< orphan*/  pgn; } ;
struct TYPE_5__ {TYPE_1__ j1939; } ;
struct sockaddr_can {TYPE_2__ can_addr; int /*<<< orphan*/  can_ifindex; int /*<<< orphan*/  can_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa; int /*<<< orphan*/  src_name; int /*<<< orphan*/  da; int /*<<< orphan*/  dst_name; int /*<<< orphan*/  pgn; } ;
struct j1939_sock {TYPE_3__ addr; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CAN ; 

__attribute__((used)) static void j1939_sk_sock2sockaddr_can(struct sockaddr_can *addr,
				       const struct j1939_sock *jsk, int peer)
{
	addr->can_family = AF_CAN;
	addr->can_ifindex = jsk->ifindex;
	addr->can_addr.j1939.pgn = jsk->addr.pgn;
	if (peer) {
		addr->can_addr.j1939.name = jsk->addr.dst_name;
		addr->can_addr.j1939.addr = jsk->addr.da;
	} else {
		addr->can_addr.j1939.name = jsk->addr.src_name;
		addr->can_addr.j1939.addr = jsk->addr.sa;
	}
}