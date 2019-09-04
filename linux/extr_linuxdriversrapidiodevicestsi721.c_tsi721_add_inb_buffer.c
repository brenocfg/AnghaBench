#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct tsi721_device {TYPE_2__* imsg_ring; TYPE_1__* pdev; } ;
struct rio_mport {struct tsi721_device* priv; } ;
struct TYPE_4__ {size_t rx_slot; scalar_t__ size; void** imq_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static int tsi721_add_inb_buffer(struct rio_mport *mport, int mbox, void *buf)
{
	struct tsi721_device *priv = mport->priv;
	u32 rx_slot;
	int rc = 0;

	rx_slot = priv->imsg_ring[mbox].rx_slot;
	if (priv->imsg_ring[mbox].imq_base[rx_slot]) {
		tsi_err(&priv->pdev->dev,
			"Error adding inbound buffer %d, buffer exists",
			rx_slot);
		rc = -EINVAL;
		goto out;
	}

	priv->imsg_ring[mbox].imq_base[rx_slot] = buf;

	if (++priv->imsg_ring[mbox].rx_slot == priv->imsg_ring[mbox].size)
		priv->imsg_ring[mbox].rx_slot = 0;

out:
	return rc;
}