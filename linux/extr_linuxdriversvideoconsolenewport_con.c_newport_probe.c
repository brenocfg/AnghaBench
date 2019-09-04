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
struct newport_regs {int dummy; } ;
struct gio_device_id {int dummy; } ;
struct TYPE_2__ {int start; } ;
struct gio_device {TYPE_1__ resource; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int do_take_over_console (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ ioremap (unsigned long,int) ; 
 int /*<<< orphan*/  newport_con ; 
 struct newport_regs* npregs ; 
 int /*<<< orphan*/  request_mem_region (unsigned long,int,char*) ; 

__attribute__((used)) static int newport_probe(struct gio_device *dev,
			 const struct gio_device_id *id)
{
	unsigned long newport_addr;
	int err;

	if (!dev->resource.start)
		return -EINVAL;

	if (npregs)
		return -EBUSY; /* we only support one Newport as console */

	newport_addr = dev->resource.start + 0xF0000;
	if (!request_mem_region(newport_addr, 0x10000, "Newport"))
		return -ENODEV;

	npregs = (struct newport_regs *)/* ioremap cannot fail */
		ioremap(newport_addr, sizeof(struct newport_regs));
	console_lock();
	err = do_take_over_console(&newport_con, 0, MAX_NR_CONSOLES - 1, 1);
	console_unlock();
	return err;
}