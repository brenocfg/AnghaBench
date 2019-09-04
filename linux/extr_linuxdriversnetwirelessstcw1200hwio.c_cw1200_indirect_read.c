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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cw1200_common {int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ST90TDS_CONFIG_REG_ID ; 
 int /*<<< orphan*/  ST90TDS_SRAM_BASE_ADDR_REG_ID ; 
 int __cw1200_reg_read (struct cw1200_common*,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int __cw1200_reg_read_32 (struct cw1200_common*,int /*<<< orphan*/ ,int*) ; 
 int __cw1200_reg_write_32 (struct cw1200_common*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int cw1200_indirect_read(struct cw1200_common *priv, u32 addr, void *buf,
			 size_t buf_len, u32 prefetch, u16 port_addr)
{
	u32 val32 = 0;
	int i, ret;

	if ((buf_len / 2) >= 0x1000) {
		pr_err("Can't read more than 0xfff words.\n");
		return -EINVAL;
	}

	priv->hwbus_ops->lock(priv->hwbus_priv);
	/* Write address */
	ret = __cw1200_reg_write_32(priv, ST90TDS_SRAM_BASE_ADDR_REG_ID, addr);
	if (ret < 0) {
		pr_err("Can't write address register.\n");
		goto out;
	}

	/* Read CONFIG Register Value - We will read 32 bits */
	ret = __cw1200_reg_read_32(priv, ST90TDS_CONFIG_REG_ID, &val32);
	if (ret < 0) {
		pr_err("Can't read config register.\n");
		goto out;
	}

	/* Set PREFETCH bit */
	ret = __cw1200_reg_write_32(priv, ST90TDS_CONFIG_REG_ID,
					val32 | prefetch);
	if (ret < 0) {
		pr_err("Can't write prefetch bit.\n");
		goto out;
	}

	/* Check for PRE-FETCH bit to be cleared */
	for (i = 0; i < 20; i++) {
		ret = __cw1200_reg_read_32(priv, ST90TDS_CONFIG_REG_ID, &val32);
		if (ret < 0) {
			pr_err("Can't check prefetch bit.\n");
			goto out;
		}
		if (!(val32 & prefetch))
			break;

		mdelay(i);
	}

	if (val32 & prefetch) {
		pr_err("Prefetch bit is not cleared.\n");
		goto out;
	}

	/* Read data port */
	ret = __cw1200_reg_read(priv, port_addr, buf, buf_len, 0);
	if (ret < 0) {
		pr_err("Can't read data port.\n");
		goto out;
	}

out:
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	return ret;
}