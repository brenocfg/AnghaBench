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
struct vmbus_channel {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct sock* get_per_channel_state (struct vmbus_channel*) ; 
 int /*<<< orphan*/  hvs_do_close_lock_held (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  vsock_sk (struct sock*) ; 

__attribute__((used)) static void hvs_close_connection(struct vmbus_channel *chan)
{
	struct sock *sk = get_per_channel_state(chan);

	lock_sock(sk);
	hvs_do_close_lock_held(vsock_sk(sk), true);
	release_sock(sk);

	/* Release the refcnt for the channel that's opened in
	 * hvs_open_connection().
	 */
	sock_put(sk);
}