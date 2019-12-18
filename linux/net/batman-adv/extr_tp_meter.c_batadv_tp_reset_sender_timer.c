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
struct batadv_tp_vars {int /*<<< orphan*/  rto; int /*<<< orphan*/  timer; int /*<<< orphan*/  sending; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void batadv_tp_reset_sender_timer(struct batadv_tp_vars *tp_vars)
{
	/* most of the time this function is invoked while normal packet
	 * reception...
	 */
	if (unlikely(atomic_read(&tp_vars->sending) == 0))
		/* timer ref will be dropped in batadv_tp_sender_cleanup */
		return;

	mod_timer(&tp_vars->timer, jiffies + msecs_to_jiffies(tp_vars->rto));
}