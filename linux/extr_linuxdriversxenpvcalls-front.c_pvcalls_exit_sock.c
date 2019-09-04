#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* sk; } ;
struct sock_mapping {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {scalar_t__ sk_send_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvcalls_exit () ; 

__attribute__((used)) static inline void pvcalls_exit_sock(struct socket *sock)
{
	struct sock_mapping *map;

	map = (struct sock_mapping *)sock->sk->sk_send_head;
	atomic_dec(&map->refcount);
	pvcalls_exit();
}