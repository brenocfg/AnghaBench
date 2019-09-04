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
struct tcp_sock {int undo_retrans; scalar_t__ retrans_out; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  undo_marker; } ;

/* Variables and functions */

__attribute__((used)) static inline void tcp_init_undo(struct tcp_sock *tp)
{
	tp->undo_marker = tp->snd_una;
	/* Retransmission still in flight may cause DSACKs later. */
	tp->undo_retrans = tp->retrans_out ? : -1;
}