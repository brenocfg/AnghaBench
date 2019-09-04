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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ max_window; scalar_t__ undo_marker; scalar_t__ snd_una; scalar_t__ snd_nxt; } ;

/* Variables and functions */
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool tcp_is_sackblock_valid(struct tcp_sock *tp, bool is_dsack,
				   u32 start_seq, u32 end_seq)
{
	/* Too far in future, or reversed (interpretation is ambiguous) */
	if (after(end_seq, tp->snd_nxt) || !before(start_seq, end_seq))
		return false;

	/* Nasty start_seq wrap-around check (see comments above) */
	if (!before(start_seq, tp->snd_nxt))
		return false;

	/* In outstanding window? ...This is valid exit for D-SACKs too.
	 * start_seq == snd_una is non-sensical (see comments above)
	 */
	if (after(start_seq, tp->snd_una))
		return true;

	if (!is_dsack || !tp->undo_marker)
		return false;

	/* ...Then it's D-SACK, and must reside below snd_una completely */
	if (after(end_seq, tp->snd_una))
		return false;

	if (!before(start_seq, tp->undo_marker))
		return true;

	/* Too old */
	if (!after(end_seq, tp->undo_marker))
		return false;

	/* Undo_marker boundary crossing (overestimates a lot). Known already:
	 *   start_seq < undo_marker and end_seq >= undo_marker.
	 */
	return !before(start_seq, end_seq - tp->max_window);
}