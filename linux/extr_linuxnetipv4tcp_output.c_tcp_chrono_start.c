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
 int /*<<< orphan*/  tcp_chrono_set (struct tcp_sock*,int const) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_chrono_start(struct sock *sk, const enum tcp_chrono type)
{
	struct tcp_sock *tp = tcp_sk(sk);

	/* If there are multiple conditions worthy of tracking in a
	 * chronograph then the highest priority enum takes precedence
	 * over the other conditions. So that if something "more interesting"
	 * starts happening, stop the previous chrono and start a new one.
	 */
	if (type > tp->chrono_type)
		tcp_chrono_set(tp, type);
}