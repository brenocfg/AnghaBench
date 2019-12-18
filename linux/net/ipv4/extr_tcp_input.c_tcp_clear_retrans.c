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
struct tcp_sock {int undo_retrans; scalar_t__ sacked_out; scalar_t__ undo_marker; scalar_t__ lost_out; scalar_t__ retrans_out; } ;

/* Variables and functions */

void tcp_clear_retrans(struct tcp_sock *tp)
{
	tp->retrans_out = 0;
	tp->lost_out = 0;
	tp->undo_marker = 0;
	tp->undo_retrans = -1;
	tp->sacked_out = 0;
}