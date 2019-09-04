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
struct socket {int dummy; } ;
struct fou {int /*<<< orphan*/  list; struct socket* sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct fou*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  udp_tunnel_sock_release (struct socket*) ; 

__attribute__((used)) static void fou_release(struct fou *fou)
{
	struct socket *sock = fou->sock;

	list_del(&fou->list);
	udp_tunnel_sock_release(sock);

	kfree_rcu(fou, rcu);
}