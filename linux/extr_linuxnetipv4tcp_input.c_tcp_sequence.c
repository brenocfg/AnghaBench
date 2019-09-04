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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {scalar_t__ rcv_nxt; int /*<<< orphan*/  rcv_wup; } ;

/* Variables and functions */
 int /*<<< orphan*/  after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_receive_window (struct tcp_sock const*) ; 

__attribute__((used)) static inline bool tcp_sequence(const struct tcp_sock *tp, u32 seq, u32 end_seq)
{
	return	!before(end_seq, tp->rcv_wup) &&
		!after(seq, tp->rcv_nxt + tcp_receive_window(tp));
}