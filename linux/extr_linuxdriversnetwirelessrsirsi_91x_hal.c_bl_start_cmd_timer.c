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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct rsi_hw {int blcmd_timer_expired; TYPE_1__ bl_cmd_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  bl_cmd_timeout ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bl_start_cmd_timer(struct rsi_hw *adapter, u32 timeout)
{
	timer_setup(&adapter->bl_cmd_timer, bl_cmd_timeout, 0);
	adapter->bl_cmd_timer.expires = (msecs_to_jiffies(timeout) + jiffies);

	adapter->blcmd_timer_expired = false;
	add_timer(&adapter->bl_cmd_timer);

	return 0;
}