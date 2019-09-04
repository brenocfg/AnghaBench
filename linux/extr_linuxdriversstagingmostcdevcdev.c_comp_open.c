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
struct inode {int /*<<< orphan*/  i_cdev; } ;
struct file {int f_flags; struct comp_channel* private_data; } ;
struct comp_channel {int access_ref; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  iface; scalar_t__ mbo_offs; int /*<<< orphan*/  dev; TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  cc; } ;
struct TYPE_3__ {scalar_t__ direction; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ MOST_CH_RX ; 
 scalar_t__ MOST_CH_TX ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 TYPE_2__ comp ; 
 int most_start_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct comp_channel* to_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int comp_open(struct inode *inode, struct file *filp)
{
	struct comp_channel *c;
	int ret;

	c = to_channel(inode->i_cdev);
	filp->private_data = c;

	if (((c->cfg->direction == MOST_CH_RX) &&
	     ((filp->f_flags & O_ACCMODE) != O_RDONLY)) ||
	     ((c->cfg->direction == MOST_CH_TX) &&
		((filp->f_flags & O_ACCMODE) != O_WRONLY))) {
		pr_info("WARN: Access flags mismatch\n");
		return -EACCES;
	}

	mutex_lock(&c->io_mutex);
	if (!c->dev) {
		pr_info("WARN: Device is destroyed\n");
		mutex_unlock(&c->io_mutex);
		return -ENODEV;
	}

	if (c->access_ref) {
		pr_info("WARN: Device is busy\n");
		mutex_unlock(&c->io_mutex);
		return -EBUSY;
	}

	c->mbo_offs = 0;
	ret = most_start_channel(c->iface, c->channel_id, &comp.cc);
	if (!ret)
		c->access_ref = 1;
	mutex_unlock(&c->io_mutex);
	return ret;
}