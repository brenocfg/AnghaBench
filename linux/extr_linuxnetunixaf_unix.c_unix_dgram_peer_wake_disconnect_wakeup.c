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
 int EPOLLOUT ; 
 int EPOLLWRBAND ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  unix_dgram_peer_wake_disconnect (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void unix_dgram_peer_wake_disconnect_wakeup(struct sock *sk,
						   struct sock *other)
{
	unix_dgram_peer_wake_disconnect(sk, other);
	wake_up_interruptible_poll(sk_sleep(sk),
				   EPOLLOUT |
				   EPOLLWRNORM |
				   EPOLLWRBAND);
}