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
typedef  int u8 ;
struct lbs_private {scalar_t__ psstate; int resp_idx; int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PS_STATE_AWAKE ; 
 scalar_t__ PS_STATE_SLEEP ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void lbs_notify_command_response(struct lbs_private *priv, u8 resp_idx)
{
	if (priv->psstate == PS_STATE_SLEEP)
		priv->psstate = PS_STATE_AWAKE;

	/* Swap buffers by flipping the response index */
	BUG_ON(resp_idx > 1);
	priv->resp_idx = resp_idx;

	wake_up(&priv->waitq);
}