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
struct wsm_buf {int dummy; } ;
struct cw1200_common {int /*<<< orphan*/  channel_switch_done; scalar_t__ channel_switch_in_progress; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_GET32 (struct wsm_buf*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static int wsm_channel_switch_indication(struct cw1200_common *priv,
					 struct wsm_buf *buf)
{
	WARN_ON(WSM_GET32(buf));

	priv->channel_switch_in_progress = 0;
	wake_up(&priv->channel_switch_done);

	wsm_unlock_tx(priv);

	return 0;

underflow:
	return -EINVAL;
}