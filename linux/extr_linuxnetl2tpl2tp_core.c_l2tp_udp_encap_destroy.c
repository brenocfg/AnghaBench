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
struct l2tp_tunnel {int dummy; } ;

/* Variables and functions */
 struct l2tp_tunnel* l2tp_tunnel (struct sock*) ; 
 int /*<<< orphan*/  l2tp_tunnel_delete (struct l2tp_tunnel*) ; 

__attribute__((used)) static void l2tp_udp_encap_destroy(struct sock *sk)
{
	struct l2tp_tunnel *tunnel = l2tp_tunnel(sk);

	if (tunnel)
		l2tp_tunnel_delete(tunnel);
}