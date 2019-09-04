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
struct TYPE_2__ {int num_sacks; } ;
struct tcp_sock {TYPE_1__ rx_opt; struct tcp_sack_block* selective_acks; } ;
struct tcp_sack_block {int /*<<< orphan*/  end_seq; int /*<<< orphan*/  start_seq; } ;

/* Variables and functions */
 scalar_t__ tcp_sack_extend (struct tcp_sack_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_sack_maybe_coalesce(struct tcp_sock *tp)
{
	int this_sack;
	struct tcp_sack_block *sp = &tp->selective_acks[0];
	struct tcp_sack_block *swalk = sp + 1;

	/* See if the recent change to the first SACK eats into
	 * or hits the sequence space of other SACK blocks, if so coalesce.
	 */
	for (this_sack = 1; this_sack < tp->rx_opt.num_sacks;) {
		if (tcp_sack_extend(sp, swalk->start_seq, swalk->end_seq)) {
			int i;

			/* Zap SWALK, by moving every further SACK up by one slot.
			 * Decrease num_sacks.
			 */
			tp->rx_opt.num_sacks--;
			for (i = this_sack; i < tp->rx_opt.num_sacks; i++)
				sp[i] = sp[i + 1];
			continue;
		}
		this_sack++, swalk++;
	}
}