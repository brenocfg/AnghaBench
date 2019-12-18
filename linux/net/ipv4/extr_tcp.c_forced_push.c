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
struct tcp_sock {int max_window; scalar_t__ pushed_seq; int /*<<< orphan*/  write_seq; } ;

/* Variables and functions */
 int after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool forced_push(const struct tcp_sock *tp)
{
	return after(tp->write_seq, tp->pushed_seq + (tp->max_window >> 1));
}