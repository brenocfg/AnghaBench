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
struct sock {int dummy; } ;
typedef  enum tcp_ca_event { ____Placeholder_tcp_ca_event } tcp_ca_event ;

/* Variables and functions */
 int CA_EVENT_CWND_RESTART ; 
 int CA_EVENT_TX_START ; 
 int /*<<< orphan*/  tcp_vegas_init (struct sock*) ; 

void tcp_vegas_cwnd_event(struct sock *sk, enum tcp_ca_event event)
{
	if (event == CA_EVENT_CWND_RESTART ||
	    event == CA_EVENT_TX_START)
		tcp_vegas_init(sk);
}