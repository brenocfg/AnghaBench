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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_ca_state; } ;

/* Variables and functions */
 scalar_t__ TCP_CA_Recovery ; 
 int /*<<< orphan*/  dctcp_react_to_loss (struct sock*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 

__attribute__((used)) static void dctcp_state(struct sock *sk, u8 new_state)
{
	if (new_state == TCP_CA_Recovery &&
	    new_state != inet_csk(sk)->icsk_ca_state)
		dctcp_react_to_loss(sk);
	/* We handle RTO in dctcp_cwnd_event to ensure that we perform only
	 * one loss-adjustment per RTT.
	 */
}