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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ ucode_trace; } ;
struct iwl_priv {int /*<<< orphan*/  ucode_trace; TYPE_1__ event_log; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 int /*<<< orphan*/  UCODE_TRACE_PERIOD ; 
 struct iwl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_continuous_event_trace (struct iwl_priv*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct iwl_priv* priv ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucode_trace ; 

__attribute__((used)) static void iwl_bg_ucode_trace(struct timer_list *t)
{
	struct iwl_priv *priv = from_timer(priv, t, ucode_trace);

	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return;

	if (priv->event_log.ucode_trace) {
		iwl_continuous_event_trace(priv);
		/* Reschedule the timer to occur in UCODE_TRACE_PERIOD */
		mod_timer(&priv->ucode_trace,
			 jiffies + msecs_to_jiffies(UCODE_TRACE_PERIOD));
	}
}