#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int /*<<< orphan*/  sock_mutex; struct connection* othercon; TYPE_2__* sock; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/ * sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CLOSE ; 
 int /*<<< orphan*/  CF_READ_PENDING ; 
 int /*<<< orphan*/  CF_WRITE_PENDING ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _stop_conn(struct connection *con, bool and_other)
{
	mutex_lock(&con->sock_mutex);
	set_bit(CF_CLOSE, &con->flags);
	set_bit(CF_READ_PENDING, &con->flags);
	set_bit(CF_WRITE_PENDING, &con->flags);
	if (con->sock && con->sock->sk) {
		write_lock_bh(&con->sock->sk->sk_callback_lock);
		con->sock->sk->sk_user_data = NULL;
		write_unlock_bh(&con->sock->sk->sk_callback_lock);
	}
	if (con->othercon && and_other)
		_stop_conn(con->othercon, false);
	mutex_unlock(&con->sock_mutex);
}