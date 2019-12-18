#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int unix_dgram_peer_wake_connect (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  unix_dgram_peer_wake_disconnect (struct sock*,struct sock*) ; 
 scalar_t__ unix_recvq_full (struct sock*) ; 

__attribute__((used)) static int unix_dgram_peer_wake_me(struct sock *sk, struct sock *other)
{
	int connected;

	connected = unix_dgram_peer_wake_connect(sk, other);

	/* If other is SOCK_DEAD, we want to make sure we signal
	 * POLLOUT, such that a subsequent write() can get a
	 * -ECONNREFUSED. Otherwise, if we haven't queued any skbs
	 * to other and its full, we will hang waiting for POLLOUT.
	 */
	if (unix_recvq_full(other) && !sock_flag(other, SOCK_DEAD))
		return 1;

	if (connected)
		unix_dgram_peer_wake_disconnect(sk, other);

	return 0;
}