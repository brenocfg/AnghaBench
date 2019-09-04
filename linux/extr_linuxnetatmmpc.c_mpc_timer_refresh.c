#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 int HZ ; 
 int MPC_P2 ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ checking_time ; 
 scalar_t__ jiffies ; 
 TYPE_1__ mpc_timer ; 

__attribute__((used)) static void mpc_timer_refresh(void)
{
	mpc_timer.expires = jiffies + (MPC_P2 * HZ);
	checking_time = mpc_timer.expires;
	add_timer(&mpc_timer);
}