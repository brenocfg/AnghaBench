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
struct wimax_dev {int dummy; } ;
struct i2400m_l3l4_hdr {int /*<<< orphan*/  type; } ;
struct i2400m {struct wimax_dev wimax_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int I2400M_MT_REPORT_MASK ; 
 int /*<<< orphan*/  d_dump (int,struct device*,struct i2400m_l3l4_hdr const*,size_t) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,char*,unsigned int,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_msg_size_check (struct i2400m*,struct i2400m_l3l4_hdr const*,size_t) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int wimax_msg (struct wimax_dev*,char*,struct i2400m_l3l4_hdr const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void i2400m_rx_trace(struct i2400m *i2400m,
		     const void *payload, size_t size)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	struct wimax_dev *wimax_dev = &i2400m->wimax_dev;
	const struct i2400m_l3l4_hdr *l3l4_hdr = payload;
	unsigned msg_type;

	result = i2400m_msg_size_check(i2400m, l3l4_hdr, size);
	if (result < 0) {
		dev_err(dev, "HW BUG? device sent a bad trace message: %d\n",
			result);
		goto error_check;
	}
	msg_type = le16_to_cpu(l3l4_hdr->type);
	d_printf(1, dev, "Trace %s 0x%04x: %zu bytes\n",
		 msg_type & I2400M_MT_REPORT_MASK ? "REPORT" : "CMD/SET/GET",
		 msg_type, size);
	d_dump(2, dev, l3l4_hdr, size);
	result = wimax_msg(wimax_dev, "trace", l3l4_hdr, size, GFP_KERNEL);
	if (result < 0)
		dev_err(dev, "error sending trace to userspace: %d\n",
			result);
error_check:
	return;
}