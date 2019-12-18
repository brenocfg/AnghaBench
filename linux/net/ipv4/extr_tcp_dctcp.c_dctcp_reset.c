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
struct tcp_sock {int /*<<< orphan*/  delivered_ce; int /*<<< orphan*/  delivered; int /*<<< orphan*/  snd_nxt; } ;
struct dctcp {int /*<<< orphan*/  old_delivered_ce; int /*<<< orphan*/  old_delivered; int /*<<< orphan*/  next_seq; } ;

/* Variables and functions */

__attribute__((used)) static void dctcp_reset(const struct tcp_sock *tp, struct dctcp *ca)
{
	ca->next_seq = tp->snd_nxt;

	ca->old_delivered = tp->delivered;
	ca->old_delivered_ce = tp->delivered_ce;
}