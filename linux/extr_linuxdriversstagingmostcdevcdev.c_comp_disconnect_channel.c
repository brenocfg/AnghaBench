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
struct most_interface {int dummy; } ;
struct comp_channel {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  wq; scalar_t__ access_ref; int /*<<< orphan*/  unlink; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  destroy_cdev (struct comp_channel*) ; 
 int /*<<< orphan*/  destroy_channel (struct comp_channel*) ; 
 struct comp_channel* get_channel (struct most_interface*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_channel (struct comp_channel*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int comp_disconnect_channel(struct most_interface *iface, int channel_id)
{
	struct comp_channel *c;

	if (!iface) {
		pr_info("Bad interface pointer\n");
		return -EINVAL;
	}

	c = get_channel(iface, channel_id);
	if (!c)
		return -ENXIO;

	mutex_lock(&c->io_mutex);
	spin_lock(&c->unlink);
	c->dev = NULL;
	spin_unlock(&c->unlink);
	destroy_cdev(c);
	if (c->access_ref) {
		stop_channel(c);
		wake_up_interruptible(&c->wq);
		mutex_unlock(&c->io_mutex);
	} else {
		mutex_unlock(&c->io_mutex);
		destroy_channel(c);
	}
	return 0;
}