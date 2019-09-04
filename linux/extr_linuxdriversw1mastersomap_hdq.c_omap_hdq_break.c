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
struct hdq_data {int hdq_irqstatus; int /*<<< orphan*/  hdq_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  hdq_spinlock; } ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OMAP_HDQ_CTRL_STATUS ; 
 int OMAP_HDQ_CTRL_STATUS_DIR ; 
 int OMAP_HDQ_CTRL_STATUS_GO ; 
 int OMAP_HDQ_CTRL_STATUS_INITIALIZATION ; 
 int OMAP_HDQ_CTRL_STATUS_PRESENCE ; 
 int /*<<< orphan*/  OMAP_HDQ_FLAG_CLEAR ; 
 int /*<<< orphan*/  OMAP_HDQ_INT_STATUS ; 
 int OMAP_HDQ_INT_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  OMAP_HDQ_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int hdq_reg_in (struct hdq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdq_reg_merge (struct hdq_data*,int /*<<< orphan*/ ,int,int) ; 
 int hdq_wait_for_flag (struct hdq_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hdq_wait_queue ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hdq_break(struct hdq_data *hdq_data)
{
	int ret = 0;
	u8 tmp_status;
	unsigned long irqflags;

	ret = mutex_lock_interruptible(&hdq_data->hdq_mutex);
	if (ret < 0) {
		dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
		ret = -EINTR;
		goto rtn;
	}

	spin_lock_irqsave(&hdq_data->hdq_spinlock, irqflags);
	/* clear interrupt flags via a dummy read */
	hdq_reg_in(hdq_data, OMAP_HDQ_INT_STATUS);
	/* ISR loads it with new INT_STATUS */
	hdq_data->hdq_irqstatus = 0;
	spin_unlock_irqrestore(&hdq_data->hdq_spinlock, irqflags);

	/* set the INIT and GO bit */
	hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS,
		OMAP_HDQ_CTRL_STATUS_INITIALIZATION | OMAP_HDQ_CTRL_STATUS_GO,
		OMAP_HDQ_CTRL_STATUS_DIR | OMAP_HDQ_CTRL_STATUS_INITIALIZATION |
		OMAP_HDQ_CTRL_STATUS_GO);

	/* wait for the TIMEOUT bit */
	ret = wait_event_timeout(hdq_wait_queue,
		hdq_data->hdq_irqstatus, OMAP_HDQ_TIMEOUT);
	if (ret == 0) {
		dev_dbg(hdq_data->dev, "break wait elapsed\n");
		ret = -EINTR;
		goto out;
	}

	tmp_status = hdq_data->hdq_irqstatus;
	/* check irqstatus */
	if (!(tmp_status & OMAP_HDQ_INT_STATUS_TIMEOUT)) {
		dev_dbg(hdq_data->dev, "timeout waiting for TIMEOUT, %x",
				tmp_status);
		ret = -ETIMEDOUT;
		goto out;
	}

	/*
	 * check for the presence detect bit to get
	 * set to show that the slave is responding
	 */
	if (!(hdq_reg_in(hdq_data, OMAP_HDQ_CTRL_STATUS) &
			OMAP_HDQ_CTRL_STATUS_PRESENCE)) {
		dev_dbg(hdq_data->dev, "Presence bit not set\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	/*
	 * wait for both INIT and GO bits rerurn to zero.
	 * zero wait time expected for interrupt mode.
	 */
	ret = hdq_wait_for_flag(hdq_data, OMAP_HDQ_CTRL_STATUS,
			OMAP_HDQ_CTRL_STATUS_INITIALIZATION |
			OMAP_HDQ_CTRL_STATUS_GO, OMAP_HDQ_FLAG_CLEAR,
			&tmp_status);
	if (ret)
		dev_dbg(hdq_data->dev, "timeout waiting INIT&GO bits"
			" return to zero, %x", tmp_status);

out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	return ret;
}