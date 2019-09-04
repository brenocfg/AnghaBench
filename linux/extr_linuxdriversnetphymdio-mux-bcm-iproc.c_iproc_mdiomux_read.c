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
struct mii_bus {int /*<<< orphan*/  dev; struct iproc_mdiomux_desc* priv; } ;
struct iproc_mdiomux_desc {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CTRL_READ_OP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int start_miim_ops (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iproc_mdiomux_read(struct mii_bus *bus, int phyid, int reg)
{
	struct iproc_mdiomux_desc *md = bus->priv;
	int ret;

	ret = start_miim_ops(md->base, phyid, reg, 0, MDIO_CTRL_READ_OP);
	if (ret < 0)
		dev_err(&bus->dev, "mdiomux read operation failed!!!");

	return ret;
}