#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct gsw_mt753x {TYPE_1__* host_bus; int /*<<< orphan*/  smi_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  (* write ) (TYPE_1__*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int MT753X_REG_ADDR_M ; 
 int MT753X_REG_ADDR_S ; 
 int MT753X_REG_PAGE_ADDR_M ; 
 int MT753X_REG_PAGE_ADDR_S ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

void mt753x_reg_write(struct gsw_mt753x *gsw, u32 reg, u32 val)
{
	mutex_lock(&gsw->host_bus->mdio_lock);

	gsw->host_bus->write(gsw->host_bus, gsw->smi_addr, 0x1f,
		(reg & MT753X_REG_PAGE_ADDR_M) >> MT753X_REG_PAGE_ADDR_S);

	gsw->host_bus->write(gsw->host_bus, gsw->smi_addr,
		(reg & MT753X_REG_ADDR_M) >> MT753X_REG_ADDR_S, val & 0xffff);

	gsw->host_bus->write(gsw->host_bus, gsw->smi_addr, 0x10, val >> 16);

	mutex_unlock(&gsw->host_bus->mdio_lock);
}