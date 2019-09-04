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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; } ;

/* Variables and functions */
 TYPE_1__ listen_sock ; 

__attribute__((used)) static void save_listen_callbacks(struct socket *sock)
{
	struct sock *sk = sock->sk;

	listen_sock.sk_data_ready = sk->sk_data_ready;
	listen_sock.sk_state_change = sk->sk_state_change;
	listen_sock.sk_write_space = sk->sk_write_space;
	listen_sock.sk_error_report = sk->sk_error_report;
}