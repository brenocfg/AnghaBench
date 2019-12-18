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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; struct ceph_connection* sk_user_data; } ;
struct ceph_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_sock_data_ready ; 
 int /*<<< orphan*/  ceph_sock_state_change ; 
 int /*<<< orphan*/  ceph_sock_write_space ; 

__attribute__((used)) static void set_sock_callbacks(struct socket *sock,
			       struct ceph_connection *con)
{
	struct sock *sk = sock->sk;
	sk->sk_user_data = con;
	sk->sk_data_ready = ceph_sock_data_ready;
	sk->sk_write_space = ceph_sock_write_space;
	sk->sk_state_change = ceph_sock_state_change;
}