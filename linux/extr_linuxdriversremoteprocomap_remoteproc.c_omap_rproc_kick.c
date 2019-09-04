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
struct TYPE_2__ {struct device* parent; } ;
struct rproc {TYPE_1__ dev; struct omap_rproc* priv; } ;
struct omap_rproc {int /*<<< orphan*/  mbox; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int mbox_send_message (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void omap_rproc_kick(struct rproc *rproc, int vqid)
{
	struct omap_rproc *oproc = rproc->priv;
	struct device *dev = rproc->dev.parent;
	int ret;

	/* send the index of the triggered virtqueue in the mailbox payload */
	ret = mbox_send_message(oproc->mbox, (void *)vqid);
	if (ret < 0)
		dev_err(dev, "failed to send mailbox message, status = %d\n",
			ret);
}