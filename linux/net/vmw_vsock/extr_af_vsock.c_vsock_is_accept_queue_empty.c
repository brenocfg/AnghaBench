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
struct vsock_sock {int /*<<< orphan*/  accept_queue; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static bool vsock_is_accept_queue_empty(struct sock *sk)
{
	struct vsock_sock *vsk = vsock_sk(sk);
	return list_empty(&vsk->accept_queue);
}