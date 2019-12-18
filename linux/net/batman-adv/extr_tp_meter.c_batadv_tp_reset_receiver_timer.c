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
struct batadv_tp_vars {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TP_RECV_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_tp_reset_receiver_timer(struct batadv_tp_vars *tp_vars)
{
	mod_timer(&tp_vars->timer,
		  jiffies + msecs_to_jiffies(BATADV_TP_RECV_TIMEOUT));
}