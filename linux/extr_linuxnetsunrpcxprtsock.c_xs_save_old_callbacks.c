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
struct sock_xprt {int /*<<< orphan*/  old_error_report; int /*<<< orphan*/  old_write_space; int /*<<< orphan*/  old_state_change; int /*<<< orphan*/  old_data_ready; } ;
struct sock {int /*<<< orphan*/  sk_error_report; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; } ;

/* Variables and functions */

__attribute__((used)) static void xs_save_old_callbacks(struct sock_xprt *transport, struct sock *sk)
{
	transport->old_data_ready = sk->sk_data_ready;
	transport->old_state_change = sk->sk_state_change;
	transport->old_write_space = sk->sk_write_space;
	transport->old_error_report = sk->sk_error_report;
}