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
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; struct connection* sk_user_data; } ;
struct connection {struct socket* sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  lowcomms_data_ready ; 
 int /*<<< orphan*/  lowcomms_error_report ; 
 int /*<<< orphan*/  lowcomms_state_change ; 
 int /*<<< orphan*/  lowcomms_write_space ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_sock(struct socket *sock, struct connection *con)
{
	struct sock *sk = sock->sk;

	write_lock_bh(&sk->sk_callback_lock);
	con->sock = sock;

	sk->sk_user_data = con;
	/* Install a data_ready callback */
	sk->sk_data_ready = lowcomms_data_ready;
	sk->sk_write_space = lowcomms_write_space;
	sk->sk_state_change = lowcomms_state_change;
	sk->sk_allocation = GFP_NOFS;
	sk->sk_error_report = lowcomms_error_report;
	write_unlock_bh(&sk->sk_callback_lock);
}