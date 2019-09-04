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
struct iwl_priv {int /*<<< orphan*/  tt_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_tt_handler(struct iwl_priv *priv)
{
	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return;

	IWL_DEBUG_TEMP(priv, "Queueing thermal throttling work.\n");
	queue_work(priv->workqueue, &priv->tt_work);
}