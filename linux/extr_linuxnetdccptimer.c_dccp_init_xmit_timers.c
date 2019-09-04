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
struct dccp_sock {int /*<<< orphan*/  dccps_xmit_timer; int /*<<< orphan*/  dccps_xmitlet; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_delack_timer ; 
 int /*<<< orphan*/  dccp_keepalive_timer ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_write_timer ; 
 int /*<<< orphan*/  dccp_write_xmit_timer ; 
 int /*<<< orphan*/  dccp_write_xmitlet ; 
 int /*<<< orphan*/  inet_csk_init_xmit_timers (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dccp_init_xmit_timers(struct sock *sk)
{
	struct dccp_sock *dp = dccp_sk(sk);

	tasklet_init(&dp->dccps_xmitlet, dccp_write_xmitlet, (unsigned long)sk);
	timer_setup(&dp->dccps_xmit_timer, dccp_write_xmit_timer, 0);
	inet_csk_init_xmit_timers(sk, &dccp_write_timer, &dccp_delack_timer,
				  &dccp_keepalive_timer);
}