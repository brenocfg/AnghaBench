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
struct cpsw_slave {int slave_num; } ;
struct cpsw_priv {struct cpsw_common* cpsw; } ;
struct cpsw_common {TYPE_1__* regs; struct cpsw_slave* slaves; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptype; } ;

/* Variables and functions */
 int CPSW_FIFO_SHAPE_EN_SHIFT ; 
 size_t cpsw_slave_index (struct cpsw_common*,struct cpsw_priv*) ; 
 int readl_relaxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpsw_fifo_shp_on(struct cpsw_priv *priv, int fifo, int on)
{
	struct cpsw_common *cpsw = priv->cpsw;
	struct cpsw_slave *slave;
	u32 shift, mask, val;

	val = readl_relaxed(&cpsw->regs->ptype);

	slave = &cpsw->slaves[cpsw_slave_index(cpsw, priv)];
	shift = CPSW_FIFO_SHAPE_EN_SHIFT + 3 * slave->slave_num;
	mask = (1 << --fifo) << shift;
	val = on ? val | mask : val & ~mask;

	writel_relaxed(val, &cpsw->regs->ptype);
}