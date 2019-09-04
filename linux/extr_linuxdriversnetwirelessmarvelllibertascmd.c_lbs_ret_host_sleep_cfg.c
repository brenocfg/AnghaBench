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
struct lbs_private {int is_host_sleep_configured; scalar_t__ psstate; int /*<<< orphan*/  host_sleep_q; scalar_t__ is_host_sleep_activated; } ;
struct cmd_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_ret_host_sleep_cfg(struct lbs_private *priv, unsigned long dummy,
			struct cmd_header *resp)
{
	if (priv->is_host_sleep_activated) {
		priv->is_host_sleep_configured = 0;
		if (priv->psstate == PS_STATE_FULL_POWER) {
			priv->is_host_sleep_activated = 0;
			wake_up_interruptible(&priv->host_sleep_q);
		}
	} else {
		priv->is_host_sleep_configured = 1;
	}

	return 0;
}