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
struct TYPE_3__ {scalar_t__ src_name; scalar_t__ sa; scalar_t__ dst_name; scalar_t__ da; } ;
struct j1939_sock {int state; scalar_t__ pgn_rx_filter; TYPE_1__ addr; int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {scalar_t__ dst_name; scalar_t__ da; scalar_t__ src_name; scalar_t__ sa; scalar_t__ pgn; } ;
struct j1939_sk_buff_cb {TYPE_2__ addr; } ;

/* Variables and functions */
 int J1939_SOCK_CONNECTED ; 
 int J1939_SOCK_PROMISC ; 
 int /*<<< orphan*/  SOCK_BROADCAST ; 
 scalar_t__ j1939_address_is_unicast (scalar_t__) ; 
 scalar_t__ j1939_pgn_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  sock_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool j1939_sk_match_dst(struct j1939_sock *jsk,
			       const struct j1939_sk_buff_cb *skcb)
{
	if ((jsk->state & J1939_SOCK_PROMISC))
		return true;

	/* Destination address filter */
	if (jsk->addr.src_name && skcb->addr.dst_name) {
		if (jsk->addr.src_name != skcb->addr.dst_name)
			return false;
	} else {
		/* receive (all sockets) if
		 * - all packages that match our bind() address
		 * - all broadcast on a socket if SO_BROADCAST
		 *   is set
		 */
		if (j1939_address_is_unicast(skcb->addr.da)) {
			if (jsk->addr.sa != skcb->addr.da)
				return false;
		} else if (!sock_flag(&jsk->sk, SOCK_BROADCAST)) {
			/* receiving broadcast without SO_BROADCAST
			 * flag is not allowed
			 */
			return false;
		}
	}

	/* Source address filter */
	if (jsk->state & J1939_SOCK_CONNECTED) {
		/* receive (all sockets) if
		 * - all packages that match our connect() name or address
		 */
		if (jsk->addr.dst_name && skcb->addr.src_name) {
			if (jsk->addr.dst_name != skcb->addr.src_name)
				return false;
		} else {
			if (jsk->addr.da != skcb->addr.sa)
				return false;
		}
	}

	/* PGN filter */
	if (j1939_pgn_is_valid(jsk->pgn_rx_filter) &&
	    jsk->pgn_rx_filter != skcb->addr.pgn)
		return false;

	return true;
}