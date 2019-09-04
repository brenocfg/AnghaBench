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
struct tcp_sock {int /*<<< orphan*/  rx_opt; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_PAWS_WINDOW ; 
 int /*<<< orphan*/  tcp_disordered_ack (struct sock const*,struct sk_buff const*) ; 
 int /*<<< orphan*/  tcp_paws_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 

__attribute__((used)) static inline bool tcp_paws_discard(const struct sock *sk,
				   const struct sk_buff *skb)
{
	const struct tcp_sock *tp = tcp_sk(sk);

	return !tcp_paws_check(&tp->rx_opt, TCP_PAWS_WINDOW) &&
	       !tcp_disordered_ack(sk, skb);
}