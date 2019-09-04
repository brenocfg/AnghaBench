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
struct TYPE_2__ {int input_buffers; } ;
struct cw1200_common {int hw_bufs_used; int /*<<< orphan*/  bh_evt_wq; TYPE_1__ wsm_caps; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int wsm_release_tx_buffer(struct cw1200_common *priv, int count)
{
	int ret = 0;
	int hw_bufs_used = priv->hw_bufs_used;

	priv->hw_bufs_used -= count;
	if (WARN_ON(priv->hw_bufs_used < 0))
		ret = -1;
	else if (hw_bufs_used >= priv->wsm_caps.input_buffers)
		ret = 1;
	if (!priv->hw_bufs_used)
		wake_up(&priv->bh_evt_wq);
	return ret;
}