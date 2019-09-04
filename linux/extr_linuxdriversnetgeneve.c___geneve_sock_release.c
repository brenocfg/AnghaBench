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
struct geneve_sock {int /*<<< orphan*/  sock; int /*<<< orphan*/  list; scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDP_TUNNEL_TYPE_GENEVE ; 
 int /*<<< orphan*/  kfree_rcu (struct geneve_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  udp_tunnel_notify_del_rx_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_tunnel_sock_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __geneve_sock_release(struct geneve_sock *gs)
{
	if (!gs || --gs->refcnt)
		return;

	list_del(&gs->list);
	udp_tunnel_notify_del_rx_port(gs->sock, UDP_TUNNEL_TYPE_GENEVE);
	udp_tunnel_sock_release(gs->sock);
	kfree_rcu(gs, rcu);
}