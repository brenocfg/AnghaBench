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
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_BAND_CFG ; 
 int /*<<< orphan*/  MT_TX_BAND_CFG_UPPER_40M ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x0_mac_set_ctrlch(struct mt76x0_dev *dev, bool primary_upper)
{
	mt76_rmw_field(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_UPPER_40M,
		       primary_upper);
}