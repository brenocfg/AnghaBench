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
struct tcp_sock {int const chrono_type; } ;
struct sock {int dummy; } ;
typedef  enum tcp_chrono { ____Placeholder_tcp_chrono } tcp_chrono ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CHRONO_BUSY ; 
 int /*<<< orphan*/  TCP_CHRONO_UNSPEC ; 
 int /*<<< orphan*/  tcp_chrono_set (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_rtx_and_write_queues_empty (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_chrono_stop(struct sock *sk, const enum tcp_chrono type)
{
	struct tcp_sock *tp = tcp_sk(sk);


	/* There are multiple conditions worthy of tracking in a
	 * chronograph, so that the highest priority enum takes
	 * precedence over the other conditions (see tcp_chrono_start).
	 * If a condition stops, we only stop chrono tracking if
	 * it's the "most interesting" or current chrono we are
	 * tracking and starts busy chrono if we have pending data.
	 */
	if (tcp_rtx_and_write_queues_empty(sk))
		tcp_chrono_set(tp, TCP_CHRONO_UNSPEC);
	else if (type == tp->chrono_type)
		tcp_chrono_set(tp, TCP_CHRONO_BUSY);
}