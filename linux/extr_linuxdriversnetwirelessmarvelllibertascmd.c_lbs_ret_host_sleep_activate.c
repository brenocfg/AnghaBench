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
struct lbs_private {int is_host_sleep_activated; int /*<<< orphan*/  host_sleep_q; } ;
struct cmd_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_ret_host_sleep_activate(struct lbs_private *priv,
		unsigned long dummy,
		struct cmd_header *cmd)
{
	priv->is_host_sleep_activated = 1;
	wake_up_interruptible(&priv->host_sleep_q);

	return 0;
}