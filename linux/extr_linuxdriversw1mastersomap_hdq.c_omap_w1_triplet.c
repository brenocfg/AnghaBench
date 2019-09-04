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
struct hdq_data {int hdq_irqstatus; int /*<<< orphan*/  hdq_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_HDQ_CTRL_STATUS ; 
 int OMAP_HDQ_CTRL_STATUS_DIR ; 
 int OMAP_HDQ_CTRL_STATUS_GO ; 
 int OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK ; 
 int OMAP_HDQ_CTRL_STATUS_SINGLE ; 
 int OMAP_HDQ_INT_STATUS_RXCOMPLETE ; 
 int OMAP_HDQ_INT_STATUS_TXCOMPLETE ; 
 int /*<<< orphan*/  OMAP_HDQ_RX_DATA ; 
 int /*<<< orphan*/  OMAP_HDQ_TIMEOUT ; 
 int /*<<< orphan*/  OMAP_HDQ_TX_DATA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int hdq_reg_in (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdq_reg_merge (void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdq_reg_out (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdq_wait_queue ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_hdq_get (void*) ; 
 int /*<<< orphan*/  omap_hdq_put (void*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 omap_w1_triplet(void *_hdq, u8 bdir)
{
	u8 id_bit, comp_bit;
	int err;
	u8 ret = 0x3; /* no slaves responded */
	struct hdq_data *hdq_data = _hdq;
	u8 ctrl = OMAP_HDQ_CTRL_STATUS_SINGLE | OMAP_HDQ_CTRL_STATUS_GO |
		  OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK;
	u8 mask = ctrl | OMAP_HDQ_CTRL_STATUS_DIR;

	omap_hdq_get(_hdq);

	err = mutex_lock_interruptible(&hdq_data->hdq_mutex);
	if (err < 0) {
		dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
		goto rtn;
	}

	hdq_data->hdq_irqstatus = 0;
	/* read id_bit */
	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS,
		      ctrl | OMAP_HDQ_CTRL_STATUS_DIR, mask);
	err = wait_event_timeout(hdq_wait_queue,
				 (hdq_data->hdq_irqstatus
				  & OMAP_HDQ_INT_STATUS_RXCOMPLETE),
				 OMAP_HDQ_TIMEOUT);
	if (err == 0) {
		dev_dbg(hdq_data->dev, "RX wait elapsed\n");
		goto out;
	}
	id_bit = (hdq_reg_in(_hdq, OMAP_HDQ_RX_DATA) & 0x01);

	hdq_data->hdq_irqstatus = 0;
	/* read comp_bit */
	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS,
		      ctrl | OMAP_HDQ_CTRL_STATUS_DIR, mask);
	err = wait_event_timeout(hdq_wait_queue,
				 (hdq_data->hdq_irqstatus
				  & OMAP_HDQ_INT_STATUS_RXCOMPLETE),
				 OMAP_HDQ_TIMEOUT);
	if (err == 0) {
		dev_dbg(hdq_data->dev, "RX wait elapsed\n");
		goto out;
	}
	comp_bit = (hdq_reg_in(_hdq, OMAP_HDQ_RX_DATA) & 0x01);

	if (id_bit && comp_bit) {
		ret = 0x03;  /* no slaves responded */
		goto out;
	}
	if (!id_bit && !comp_bit) {
		/* Both bits are valid, take the direction given */
		ret = bdir ? 0x04 : 0;
	} else {
		/* Only one bit is valid, take that direction */
		bdir = id_bit;
		ret = id_bit ? 0x05 : 0x02;
	}

	/* write bdir bit */
	hdq_reg_out(_hdq, OMAP_HDQ_TX_DATA, bdir);
	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS, ctrl, mask);
	err = wait_event_timeout(hdq_wait_queue,
				 (hdq_data->hdq_irqstatus
				  & OMAP_HDQ_INT_STATUS_TXCOMPLETE),
				 OMAP_HDQ_TIMEOUT);
	if (err == 0) {
		dev_dbg(hdq_data->dev, "TX wait elapsed\n");
		goto out;
	}

	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS, 0,
		      OMAP_HDQ_CTRL_STATUS_SINGLE);

out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	omap_hdq_put(_hdq);
	return ret;
}