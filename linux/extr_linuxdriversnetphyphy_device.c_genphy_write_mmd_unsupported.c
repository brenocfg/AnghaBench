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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int genphy_write_mmd_unsupported(struct phy_device *phdev, int devnum,
				 u16 regnum, u16 val)
{
	return -EOPNOTSUPP;
}