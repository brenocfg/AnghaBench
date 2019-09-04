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
struct hdq_data {scalar_t__ init_trans; int /*<<< orphan*/  hdq_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  OMAP_HDQ_CTRL_STATUS ; 
 int /*<<< orphan*/  OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hdq_disable_interrupt (struct hdq_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdq_read_byte (struct hdq_data*,int*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_hdq_get (struct hdq_data*) ; 
 int /*<<< orphan*/  omap_hdq_put (struct hdq_data*) ; 

__attribute__((used)) static u8 omap_w1_read_byte(void *_hdq)
{
	struct hdq_data *hdq_data = _hdq;
	u8 val = 0;
	int ret;

	/* First write to initialize the transfer */
	if (hdq_data->init_trans == 0)
		omap_hdq_get(hdq_data);

	ret = hdq_read_byte(hdq_data, &val);
	if (ret) {
		ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
		if (ret < 0) {
			dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
			return -EINTR;
		}
		hdq_data->init_trans = 0;
		mutex_unlock(&hdq_data->hdq_mutex);
		omap_hdq_put(hdq_data);
		return -1;
	}

	hdq_disable_interrupt(hdq_data, OMAP_HDQ_CTRL_STATUS,
			      ~OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK);

	/* Write followed by a read, release the module */
	if (hdq_data->init_trans) {
		ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
		if (ret < 0) {
			dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
			return -EINTR;
		}
		hdq_data->init_trans = 0;
		mutex_unlock(&hdq_data->hdq_mutex);
		omap_hdq_put(hdq_data);
	}

	return val;
}