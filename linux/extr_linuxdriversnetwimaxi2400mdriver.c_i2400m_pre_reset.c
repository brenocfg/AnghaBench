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
struct TYPE_2__ {int /*<<< orphan*/  net_dev; } ;
struct i2400m {int /*<<< orphan*/  (* bus_release ) (struct i2400m*) ;int /*<<< orphan*/  init_mutex; TYPE_1__ wimax_dev; scalar_t__ updown; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i2400m_dev_stop (struct i2400m*) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct i2400m*) ; 

int i2400m_pre_reset(struct i2400m *i2400m)
{
	struct device *dev = i2400m_dev(i2400m);

	d_fnstart(3, dev, "(i2400m %p)\n", i2400m);
	d_printf(1, dev, "pre-reset shut down\n");

	mutex_lock(&i2400m->init_mutex);
	if (i2400m->updown) {
		netif_tx_disable(i2400m->wimax_dev.net_dev);
		__i2400m_dev_stop(i2400m);
		/* down't set updown to zero -- this way
		 * post_reset can restore properly */
	}
	mutex_unlock(&i2400m->init_mutex);
	if (i2400m->bus_release)
		i2400m->bus_release(i2400m);
	d_fnend(3, dev, "(i2400m %p) = 0\n", i2400m);
	return 0;
}