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
typedef  scalar_t__ u32 ;
struct i2400m_bcf_hdr {int /*<<< orphan*/  module_id; } ;
struct i2400m {struct i2400m_bcf_hdr** fw_hdrs; TYPE_1__* barker; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ I2400M_NBOOT_BARKER ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 scalar_t__ i2400m_bcf_hdr_match (struct i2400m*,struct i2400m_bcf_hdr const*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
const struct i2400m_bcf_hdr *i2400m_bcf_hdr_find(struct i2400m *i2400m)
{
	struct device *dev = i2400m_dev(i2400m);
	const struct i2400m_bcf_hdr **bcf_itr, *bcf_hdr;
	unsigned i = 0;
	u32 barker = le32_to_cpu(i2400m->barker->data[0]);

	d_printf(2, dev, "finding BCF header for barker %08x\n", barker);
	if (barker == I2400M_NBOOT_BARKER) {
		bcf_hdr = i2400m->fw_hdrs[0];
		d_printf(1, dev, "using BCF header #%u/%08x for non-signed "
			 "barker\n", 0, le32_to_cpu(bcf_hdr->module_id));
		return bcf_hdr;
	}
	for (bcf_itr = i2400m->fw_hdrs; *bcf_itr != NULL; bcf_itr++, i++) {
		bcf_hdr = *bcf_itr;
		if (i2400m_bcf_hdr_match(i2400m, bcf_hdr)) {
			d_printf(1, dev, "hit on BCF hdr #%u/%08x\n",
				 i, le32_to_cpu(bcf_hdr->module_id));
			return bcf_hdr;
		} else
			d_printf(1, dev, "miss on BCF hdr #%u/%08x\n",
				 i, le32_to_cpu(bcf_hdr->module_id));
	}
	dev_err(dev, "cannot find a matching BCF header for barker %08x\n",
		barker);
	return NULL;
}