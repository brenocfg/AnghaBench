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
typedef  int u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88179_PHY_ID ; 
 int /*<<< orphan*/  AX_ACCESS_PHY ; 
 int /*<<< orphan*/  MII_MMD_CTRL ; 
 int MII_MMD_CTRL_NOINCR ; 
 int /*<<< orphan*/  MII_MMD_DATA ; 
 int ax88179_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static inline int ax88179_phy_mmd_indirect(struct usbnet *dev, u16 prtad,
					   u16 devad)
{
	u16 tmp16;
	int ret;

	tmp16 = devad;
	ret = ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_CTRL, 2, &tmp16);

	tmp16 = prtad;
	ret = ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_DATA, 2, &tmp16);

	tmp16 = devad | MII_MMD_CTRL_NOINCR;
	ret = ax88179_write_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_CTRL, 2, &tmp16);

	return ret;
}