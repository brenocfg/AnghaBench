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
struct timer_list {int dummy; } ;
struct il_priv {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 struct il_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct il_priv* il ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int /*<<< orphan*/  il_send_stats_request (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_periodic ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il4965_bg_stats_periodic(struct timer_list *t)
{
	struct il_priv *il = from_timer(il, t, stats_periodic);

	if (test_bit(S_EXIT_PENDING, &il->status))
		return;

	/* dont send host command if rf-kill is on */
	if (!il_is_ready_rf(il))
		return;

	il_send_stats_request(il, CMD_ASYNC, false);
}