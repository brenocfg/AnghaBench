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
struct socket {int /*<<< orphan*/  state; int /*<<< orphan*/ * sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_FREE ; 
 int /*<<< orphan*/  __vsock_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsock_release(struct socket *sock)
{
	__vsock_release(sock->sk, 0);
	sock->sk = NULL;
	sock->state = SS_FREE;

	return 0;
}