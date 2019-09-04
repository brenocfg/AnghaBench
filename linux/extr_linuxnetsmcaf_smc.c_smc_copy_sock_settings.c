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
struct sock {unsigned long sk_flags; int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_rcvlowat; int /*<<< orphan*/  sk_priority; int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_rcvtimeo; int /*<<< orphan*/  sk_sndtimeo; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_type; } ;

/* Variables and functions */

__attribute__((used)) static void smc_copy_sock_settings(struct sock *nsk, struct sock *osk,
				   unsigned long mask)
{
	/* options we don't get control via setsockopt for */
	nsk->sk_type = osk->sk_type;
	nsk->sk_sndbuf = osk->sk_sndbuf;
	nsk->sk_rcvbuf = osk->sk_rcvbuf;
	nsk->sk_sndtimeo = osk->sk_sndtimeo;
	nsk->sk_rcvtimeo = osk->sk_rcvtimeo;
	nsk->sk_mark = osk->sk_mark;
	nsk->sk_priority = osk->sk_priority;
	nsk->sk_rcvlowat = osk->sk_rcvlowat;
	nsk->sk_bound_dev_if = osk->sk_bound_dev_if;
	nsk->sk_err = osk->sk_err;

	nsk->sk_flags &= ~mask;
	nsk->sk_flags |= osk->sk_flags & mask;
}