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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int (* read_bulk ) (struct bq27xxx_device_info*,scalar_t__,int /*<<< orphan*/ *,int) ;} ;
struct bq27xxx_device_info {scalar_t__* regs; int /*<<< orphan*/  dev; TYPE_1__ bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ INVALID_REG_ADDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int stub1 (struct bq27xxx_device_info*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int bq27xxx_read_block(struct bq27xxx_device_info *di, int reg_index,
				     u8 *data, int len)
{
	int ret;

	if (!di || di->regs[reg_index] == INVALID_REG_ADDR)
		return -EINVAL;

	if (!di->bus.read_bulk)
		return -EPERM;

	ret = di->bus.read_bulk(di, di->regs[reg_index], data, len);
	if (ret < 0)
		dev_dbg(di->dev, "failed to read_bulk register 0x%02x (index %d)\n",
			di->regs[reg_index], reg_index);

	return ret;
}