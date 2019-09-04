#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_3__ {struct sock sk; } ;
struct TYPE_4__ {TYPE_1__ icsk_inet; } ;
struct dccp_sock {TYPE_2__ dccps_inet_connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_write_xmitlet (unsigned long) ; 
 int /*<<< orphan*/  dccps_xmit_timer ; 
 struct dccp_sock* dp ; 
 struct dccp_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_write_xmit_timer(struct timer_list *t)
{
	struct dccp_sock *dp = from_timer(dp, t, dccps_xmit_timer);
	struct sock *sk = &dp->dccps_inet_connection.icsk_inet.sk;

	dccp_write_xmitlet((unsigned long)sk);
}