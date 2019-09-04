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
typedef  int u32 ;
struct gbe_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GBE_REG_ADDR (struct gbe_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RGMII_REG_STATUS_LINK ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgmii_status ; 
 int /*<<< orphan*/  ss_regs ; 

__attribute__((used)) static void netcp_2u_rgmii_get_port_link(struct gbe_priv *gbe_dev, bool *status)
{
	u32 val = 0;

	val = readl(GBE_REG_ADDR(gbe_dev, ss_regs, rgmii_status));
	*status = !!(val & RGMII_REG_STATUS_LINK);
}